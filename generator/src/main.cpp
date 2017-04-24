#include <iostream>
#include <unordered_map>

#define CSV_IO_NO_THREAD
#include "csv.h"

#include "stringsymbolizer.h"
#include "passthroughsymbolizer.h"
#include "rangesymbolizer.h"

#include "autovector.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./naive_bayes [csv_file]" << std::endl;
        return 1;
    }

    static constexpr unsigned int num_columns = 6;
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
    unsigned int output_col = 5;

    //StringSymbolizer year_symb;
    StringSymbolizer outlook_symb;
    RangeSymbolizer temp_symb; temp_symb.add_split(30); temp_symb.add_split(40); temp_symb.add_split(50); temp_symb.add_split(60); temp_symb.add_split(70);
    RangeSymbolizer wind_symb; wind_symb.add_split(2); wind_symb.add_split(4); wind_symb.add_split(6); wind_symb.add_split(10);
    StringSymbolizer season_symb;
    RangeSymbolizer humidity_symb; humidity_symb.add_split(40); humidity_symb.add_split(50); humidity_symb.add_split(60); humidity_symb.add_split(70); humidity_symb.add_split(80);
    StringSymbolizer up_down_symb;


    AutoVector<std::array<AutoVector<unsigned int>, num_columns>> counts;

    unsigned int rows = 0;

    //std::string year;
    std::string outlook;
    double temp;
    double wind;
    std::string season;
    double humidity;
    std::string up_down;

    while(in.read_row(/*year, */outlook, temp, wind, season, humidity, up_down)){
        unsigned int features[num_columns] = {
            //year_symb.index(year),
            outlook_symb.index(outlook),
            temp_symb.index(temp),
            wind_symb.index(wind),
            season_symb.index(season),
            humidity_symb.index(humidity),
            up_down_symb.index(up_down),
        };

        std::array<AutoVector<unsigned int>, num_columns> &result_counts = counts[features[output_col]];
        for (unsigned int i = 0; i < num_columns; i++) {
            result_counts[i][features[i]]++;
        }
        rows++;
    }

    std::string func;

    func += "function compute(outlook, temp, wind, season, humidity) {\n";
    func += "let features = [];\n";
    //func += year_symb.make_transform_func("features[???]", "year");
    func += outlook_symb.make_transform_func("features[0]", "outlook");
    func += temp_symb.make_transform_func("features[1]", "temp");
    func += wind_symb.make_transform_func("features[2]", "wind");
    func += season_symb.make_transform_func("features[3]", "season");
    func += humidity_symb.make_transform_func("features[4]", "humidity");

    func += "let data = [\n";

    AutoVector<std::array<AutoVector<unsigned int>, num_columns>>::const_iterator i = counts.cbegin();
    while (i != counts.cend()) {
        func += "[";
        for (unsigned int j = 0; j < num_columns; j++) {
            func += "[";
            const AutoVector<unsigned int> &histogram = (*i)[j];
            AutoVector<unsigned int>::const_iterator k = histogram.cbegin();
            while (k != histogram.cend()) {
                func += std::to_string(*k) + ", ";
                k++;
            }
            func += "], ";
        }
        func += "],\n";
        i++;
    }
    func += "];\n";

    func += "let probs = {};\n";
    func += "data.forEach(function(result, i) {\n";
    func += "    let total = result[" + std::to_string(output_col) + "][i];\n";
    func += "    let prob = total / " + std::to_string(rows) + ";\n";
    func += "    result.forEach(function(histogram, j) {\n";
    func += "        if (j == " + std::to_string(output_col) + ") {return;}\n";
    func += "        prob *= histogram[features[j]] / total;\n";
    func += "    });\n";
    func += up_down_symb.make_reverse_func("key", "i");
    func += "    probs[key] = prob;\n";
    func += "});\n";
    func += "return probs;\n";
    func += "};\n";

    std::cout << func << std::endl;

    return 0;
}
