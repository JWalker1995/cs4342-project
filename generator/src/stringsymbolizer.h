#ifndef STRINGSYMBOLIZER_H
#define STRINGSYMBOLIZER_H

#include <string>
#include <unordered_map>

class StringSymbolizer {
public:
    unsigned int index(const std::string &data);
    std::string make_transform_func(const std::string &output_var, const std::string &input_var) const;
    std::string make_reverse_func(const std::string &output_var, const std::string &input_var) const;

private:
    unsigned int next_class = 0;
    std::unordered_map<std::string, unsigned int> values;
};

#endif // STRINGSYMBOLIZER_H