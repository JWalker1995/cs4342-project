#include <iostream>
#include <unordered_map>

#define CSV_IO_NO_THREAD
#include "csv.h"


class StringSymbolizer {
public:
    unsigned int index(const std::string &data) {
        std::pair<std::unordered_map<std::string, unsigned int>::const_iterator, bool> res = values.emplace(data, next_class);
        if (res.second) {
            next_class++;
        }
        return res.first->second;
    }

    std::string make_transform_func(const std::string &output_var, const std::string &input_var) const {
        std::string res;
        res += output_var + " = {\n";
        std::unordered_map<std::string, unsigned int>::const_iterator i = values.cbegin();
        while (i != values.cend()) {
            res += "\"" + i->first + "\": " + std::to_string(i->second) + ",\n";
            i++;
        }
        res += "}[" + input_var + "];\n";
        res += "if (typeof " + output_var + " === 'undefined') {\n";
        res += "throw new Error('Invalid value in variable " + input_var + ": ' + JSON.stringify(" + input_var + "));\n";
        res += "}\n";
        return res;
    }

    std::string make_reverse_func(const std::string &output_var, const std::string &input_var) const {
        std::string res;
        res += output_var + " = {\n";
        std::unordered_map<std::string, unsigned int>::const_iterator i = values.cbegin();
        while (i != values.cend()) {
            res += "\"" + std::to_string(i->second) + "\": \"" + i->first + "\",\n";
            i++;
        }
        res += "}[" + input_var + "];\n";
        res += "if (typeof " + output_var + " === 'undefined') {\n";
        res += "throw new Error('Invalid value in variable " + input_var + ": ' + JSON.stringify(" + input_var + "));\n";
        res += "}\n";
        return res;
    }

private:
    unsigned int next_class = 0;
    std::unordered_map<std::string, unsigned int> values;
};

class PassthroughSymbolizer {
public:
    unsigned int index(unsigned int value) {
        return value;
    }

    std::string make_transform_func(const std::string &output_var, const std::string &input_var) const {
        return output_var + " = " + input_var + ";\n";
    }
};

class RangeSymbolizer {
public:
    void add_split(double split) {
        splits.push_back(split);
    }

    unsigned int index(double value) {
        return std::upper_bound(splits.cbegin(), splits.cend(), value) - splits.cbegin();
    }

    std::string make_transform_func(const std::string &output_var, const std::string &input_var) const {
        if (splits.empty()) {
            std::cerr << "RangeSymbolizer::splits is empty!" << std::endl;
            std::exit(1);
        }
        std::string res;
        std::vector<double>::const_iterator i = splits.cbegin();
        while (i != splits.cend()) {
            if (i != splits.cbegin()) {
                res += "else ";
            }
            res += "if (" + input_var + " < " + std::to_string(*i) + ") {";
            res += output_var + " = " + std::to_string(i - splits.cbegin()) + ";";
            res += "}\n";
            i++;
        }
        res += "else {" + output_var + " = " + std::to_string(splits.size()) + ";}\n";
        return res;
    }

private:
    std::vector<double> splits;
};

template <typename ElementType>
class AutoVector : public std::vector<ElementType>{
public:
    ElementType &operator[](unsigned int index) {
        if (index >= std::vector<ElementType>::size()) {
            std::vector<ElementType>::resize(index + 1);
        }
        return std::vector<ElementType>::operator[](index);
    }
};


int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./naive_bayes [csv_file]" << std::endl;
        return 1;
    }

    static constexpr unsigned int num_columns = 7;
    io::CSVReader<num_columns> in(argv[1]);

    in.read_header(io::ignore_extra_column,
                   "year",
                   "outlook",
                   "temp",
                   "wind",
                   "season",
                   "humidity",
                   "up/down"
                   /* "market difference", "current day", "previous day" */
                   );
    unsigned int output_col = 6;

    StringSymbolizer year_symb;
    StringSymbolizer outlook_symb;
    RangeSymbolizer temp_symb; temp_symb.add_split(30); temp_symb.add_split(40); temp_symb.add_split(50); temp_symb.add_split(60); temp_symb.add_split(70);
    RangeSymbolizer wind_symb; wind_symb.add_split(2); wind_symb.add_split(4); wind_symb.add_split(6); wind_symb.add_split(10);
    StringSymbolizer season_symb;
    RangeSymbolizer humidity_symb; humidity_symb.add_split(40); humidity_symb.add_split(50); humidity_symb.add_split(60); humidity_symb.add_split(70); humidity_symb.add_split(80);
    StringSymbolizer up_down_symb;


    AutoVector<std::array<AutoVector<unsigned int>, num_columns>> counts;

    unsigned int rows = 0;

    std::string year;
    std::string outlook;
    double temp;
    double wind;
    std::string season;
    double humidity;
    std::string up_down;

    while(in.read_row(year, outlook, temp, wind, season, humidity, up_down)){
        unsigned int features[num_columns] = {
            year_symb.index(year),
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

    func += "window.classify = function(year, outlook, temp, wind, season, humidity) {\n";
    func += "let features = [];\n";
    func += year_symb.make_transform_func("features[0]", "year");
    func += outlook_symb.make_transform_func("features[1]", "outlook");
    func += temp_symb.make_transform_func("features[2]", "temp");
    func += wind_symb.make_transform_func("features[3]", "wind");
    func += season_symb.make_transform_func("features[4]", "season");
    func += humidity_symb.make_transform_func("features[5]", "humidity");

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

    func += "let max_prob = 0;\n";
    func += "let max_val;\n";
    func += "data.forEach(function(result, i) {\n";
    func += "    let total = result[" + std::to_string(output_col) + "][i];\n";
    func += "    let prob = total / " + std::to_string(rows) + ";\n";
    func += "    result.forEach(function(histogram, j) {\n";
    func += "        if (j == " + std::to_string(output_col) + ") {return;}\n";
    func += "        prob *= histogram[features[j]] / total;\n";
    func += "    });\n";
    func += "    if (prob > max_prob) {\n";
    func += "        max_prob = prob;\n";
    func += "        max_val = i;\n";
    func += "    }\n";
    func += "});\n";
    func += up_down_symb.make_reverse_func("result", "max_val");
    func += "return result;\n";

    func += "};\n";

    std::cout << func << std::endl;

    return 0;
}
