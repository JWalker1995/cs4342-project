#include <iostream>
#include <unordered_map>

#define CSV_IO_NO_THREAD
#include "3rd_party/csv.h"

#include "symbolizers/stringsymbolizer.h"
#include "symbolizers/passthroughsymbolizer.h"
#include "symbolizers/rangesymbolizer.h"

#include "sample.h"

static constexpr unsigned int num_columns = 6;

#include "naive_bayes/builder.h"
#include "decision_tree/builder.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./generator [csv_file]" << std::endl;
        return 1;
    }
    
    Sample::num_features = 5;
    
    io::CSVReader<num_columns> in(argv[1]);

    in.read_header(io::ignore_extra_column,
                   /*"year",*/
                   "outlook",
                   "temp",
                   "wind",
                   "season",
                   "humidity",
                   "up/down"
                   /* "market difference", "current day", "previous day" */
                   );

    //StringSymbolizer year_symb;
    StringSymbolizer outlook_symb;
    RangeSymbolizer temp_symb; temp_symb.add_split(30); temp_symb.add_split(40); temp_symb.add_split(50); temp_symb.add_split(60); temp_symb.add_split(70);
    RangeSymbolizer wind_symb; wind_symb.add_split(2); wind_symb.add_split(4); wind_symb.add_split(6); wind_symb.add_split(10);
    StringSymbolizer season_symb;
    RangeSymbolizer humidity_symb; humidity_symb.add_split(40); humidity_symb.add_split(50); humidity_symb.add_split(60); humidity_symb.add_split(70); humidity_symb.add_split(80);
    StringSymbolizer up_down_symb;

    naive_bayes::Builder naive_bayes_builder;
    decision_tree::Builder decision_tree_builder;

    //std::string year;
    std::string outlook;
    double temp;
    double wind;
    std::string season;
    double humidity;
    std::string up_down;

    while(in.read_row(/*year, */outlook, temp, wind, season, humidity, up_down)) {
        Sample sample;
        
        sample.set_feature(0, outlook_symb.index(outlook));
        sample.set_feature(1, temp_symb.index(temp));
        sample.set_feature(2, wind_symb.index(wind));
        sample.set_feature(3, season_symb.index(season));
        sample.set_feature(4, humidity_symb.index(humidity));
        sample.set_result(up_down_symb.index(up_down));
        
        naive_bayes_builder.add_sample(sample);
        decision_tree_builder.add_sample(sample);
    }
    
    
    TreeParams tree_params;
    tree_params.min_samples_to_split = 1;
    tree_params.min_gain_to_split = 0.01f; // Must be greater than zero

    std::string func;

    func += "function compute(outlook, temp, wind, season, humidity) {\n";
    func += "let features = [];\n";
    
    // Convert feature strings and ranges into the feature ids
    func += outlook_symb.make_transform_func("features[0]", "outlook");
    func += temp_symb.make_transform_func("features[1]", "temp");
    func += wind_symb.make_transform_func("features[2]", "wind");
    func += season_symb.make_transform_func("features[3]", "season");
    func += humidity_symb.make_transform_func("features[4]", "humidity");
    
    // Define categorization functions
    func += "let nb_func = " + naive_bayes_builder.to_js_code() + ";\n";
    func += "let dt_func = " + decision_tree_builder.to_js_code(tree_params) + ";\n";
    
    // Call categorization functions
    func += "let nb_arr = nb_func(features);\n";
    func += "let dt_arr = dt_func(features);\n";
    
    func += "let nb_obj = {};\n";
    func += "let dt_obj = {};\n";
    
    // Convert array of probabilities into an object mapping from the class string to a probability
    func += "nb_res.forEach(function(val, index) {\n";
    func += up_down_symb.make_reverse_func("key", "index");
    func += "nb_obj[key] = val;\n";
    func += "});\n";
    
    func += "dt_res.forEach(function(val, index) {\n";
    func += up_down_symb.make_reverse_func("key", "index");
    func += "dt_obj[key] = val;\n";
    func += "});\n";
    
    // Return it
    func += "return {'nb_obj': nb_obj, 'dt_obj': dt_obj'};\n";
    
    func += "};\n"
    
    std::cout << func << std::endl;

    return 0;
}
