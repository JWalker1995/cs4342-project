#ifndef DT_SPLITTER_H
#define DT_SPLITTER_H

#include <vector>

#include "../sample.h"

namespace decision_tree {

class TreeParams;
class DecisionNode;

class Splitter {
public:
    void add_sample(const Sample &sample);

    const DecisionNode *create_tree(const TreeParams &params) const;

private:
    std::vector<Sample> samples;

    std::pair<unsigned int, float> calc_split(const TreeParams &params) const;
    float calc_remainder(unsigned int feature_index) const;
    float calc_entropy_times_prob() const;
    float calc_entropy_times_prob(unsigned int feature_index, unsigned int feature_val) const;
    unsigned int get_frequent_result() const;
    void build_histogram(std::vector<unsigned int> &histogram, unsigned int &total, unsigned int feature_index, unsigned int feature_val) const;
    const DecisionNode *split_on(unsigned int split_index, const TreeParams &params) const;
};

}

#endif // DT_SPLITTER_H
