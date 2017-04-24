#include "passthroughsymbolizer.h"

unsigned int PassthroughSymbolizer::index(unsigned int value) {
    return value;
}

std::string PassthroughSymbolizer::make_transform_func(const std::string &output_var, const std::string &input_var) const {
    return output_var + " = " + input_var + ";\n";
}
