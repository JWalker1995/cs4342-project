#ifndef DT_BUILDER_H
#define DT_BUILDER_H

#include "../sample.h"
#include "splitter.h"

namespace decision_tree {

class Builder {
public:
    Builder();
    
    void add_sample(Sample sample);
    std::string to_js_code(const TreeParams &params) const;
    
private:
    Splitter root;
};

}

#endif // DT_BUILDER_H