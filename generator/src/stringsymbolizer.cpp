#include "stringsymbolizer.h"

unsigned int StringSymbolizer::index(const std::string &data) {
    std::pair<std::unordered_map<std::string, unsigned int>::const_iterator, bool> res = values.emplace(data, next_class);
    if (res.second) {
        next_class++;
    }
    return res.first->second;
}

std::string StringSymbolizer::make_transform_func(const std::string &output_var, const std::string &input_var) const {
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

std::string StringSymbolizer::make_reverse_func(const std::string &output_var, const std::string &input_var) const {
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