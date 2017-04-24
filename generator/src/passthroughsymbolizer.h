#ifndef PASSTHROUGHSYMBOLIZER_H
#define PASSTHROUGHSYMBOLIZER_H

#include <string>

class PassthroughSymbolizer {
public:
    unsigned int index(unsigned int value);
    std::string make_transform_func(const std::string &output_var, const std::string &input_var) const;
};

#endif // PASSTHROUGHSYMBOLIZER_H