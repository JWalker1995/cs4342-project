#ifndef RANGESYMBOLIZER_H
#define RANGESYMBOLIZER_H

#include <string>
#include <vector>

class RangeSymbolizer {
public:
    void add_split(double split);
    unsigned int index(double value);
    std::string make_transform_func(const std::string &output_var, const std::string &input_var) const;

private:
    std::vector<double> splits;
};

#endif // RANGESYMBOLIZER_H