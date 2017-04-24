#include "decisionnode.h"

#include "../sample.h"

namespace decision_tree {

DecisionNode *DecisionNode::create_leaf(unsigned int classification) {
    DecisionNode *res = new DecisionNode();
    res->classification = classification;
    return res;
}

DecisionNode *DecisionNode::create_branch(unsigned int split_index) {
    DecisionNode *res = new DecisionNode();
    res->classification = static_cast<unsigned int>(-1);
    res->split_index = split_index;
    return res;
}

bool DecisionNode::is_leaf() const {
    return classification != static_cast<unsigned int>(-1);
}

void DecisionNode::add_child(const DecisionNode *child) {
    assert(!is_leaf());
    children.push_back(child);
}

unsigned int DecisionNode::classify(const Sample &sample) const {
    if (is_leaf()) {
        return classification;
    } else {
        unsigned int value = sample.get_feature(split_index);
        assert(value < children.size());
        return children[value]->classify(sample);
    }
}

std::string DecisionNode::to_string(unsigned int indent) const {
    std::string res;
    if (is_leaf()) {
        res += std::to_string(classification);
        res += '\n';
    } else {
        res += "switch on feature[" + std::to_string(split_index) + "]";
        res += '\n';

        indent++;
        std::string indent_str(indent * 2, ' ');

        std::vector<const DecisionNode *>::const_iterator i = children.cbegin();
        while (i != children.cend()) {
            res += indent_str + std::to_string(i - children.cbegin()) + ": " + (*i)->to_string(indent);
            i++;
        }
    }
    return res;
}

std::string DecisionNode::to_js_code() const {
    std::string res;
    if (is_leaf()) {
        res += "return " + std::to_string(classification) + ";\n";
    } else {
        std::string feature_code = "features[" + std::to_string(split_index) + "]";

        res += "switch (" + feature_code + ") {\n";

        std::vector<const DecisionNode *>::const_iterator i = children.cbegin();
        while (i != children.cend()) {
            res += "case " + std::to_string(i - children.cbegin()) + ":\n";
            res += (*i)->to_js_code();
            i++;
        }

        res += "default:\n";
        res += "throw new Error('Invalid " + feature_code + ":' + " + feature_code + ");\n";
        res += "}";
    }
    return res;
}

}
