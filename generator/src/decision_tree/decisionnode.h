#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include <vector>
#include <string>

class Sample;

class DecisionNode {
public:
    static DecisionNode *create_leaf(unsigned int classification);
    static DecisionNode *create_branch(unsigned int split_index);

    bool is_leaf() const;

    void add_child(const DecisionNode *child);

    unsigned int classify(const Sample &sample) const;

    std::string to_string(unsigned int indent = 0) const;

    std::string to_js_code() const;

private:
    unsigned int classification;

    unsigned int split_index;
    std::vector<const DecisionNode *> children;
};

#endif // DECISIONNODE_H
