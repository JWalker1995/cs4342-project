#include "builder.h"

namespace decision_tree {

void Builder::add_sample(Sample sample) {
    root.add_sample(sample);
}

std::string Builder::to_js_code(const TreeParams &params) const {
    const DecisionNode *decision_tree = root.create_tree(params);
    
    std::string res;

    res += "function(features) {\n";
    res += "let index = (function() {\n";
    res += decision_tree->to_js_code();
    res += "})();";
    res += "let res = [];\n";
    res += "res[index] = 1.0;\n";
    res += "return res;\n";
    res += "}";
    
    return res;
}

}