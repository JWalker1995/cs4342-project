#include "rangesymbolizer.h"

#include "symbolizerexception.h"

#include <algorithm>

void RangeSymbolizer::add_split(double split) {
    splits.push_back(split);
}

unsigned int RangeSymbolizer::index(double value) {
    return std::upper_bound(splits.cbegin(), splits.cend(), value) - splits.cbegin();
}

std::string RangeSymbolizer::make_transform_func(const std::string &output_var, const std::string &input_var) const {
    if (splits.empty()) {
        throw SymbolizerException("RangeSymbolizer::splits is empty!");
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
