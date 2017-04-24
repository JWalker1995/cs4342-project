#include "splitter.h"

#include <cmath>
#include <algorithm>

#include "treeparams.h"
#include "decisionnode.h"

namespace decision_tree {

void Splitter::add_sample(const Sample &sample) {
    samples.push_back(sample);
}

const DecisionNode *Splitter::create_tree(const TreeParams &params) const {
    if (samples.size() >= params.min_samples_to_split) {
        std::pair<unsigned int, float> split = calc_split(params);
        unsigned int split_index = split.first;

        if (split_index != static_cast<unsigned int>(-1)) {
            float gain = split.second;
            if (gain >= params.min_gain_to_split) {
                return split_on(split_index, params);
            }
        }
    }

    unsigned int classification = get_frequent_result();
    return DecisionNode::create_leaf(classification);
}

std::pair<unsigned int, float> Splitter::calc_split(const TreeParams &params) const {
    unsigned int best_index = static_cast<unsigned int>(-1);
    float best_remainder = 1.0e6f;
    for (unsigned int i = 0; i < Sample::num_features; i++) {
        if (std::find(params.used_features.cbegin(), params.used_features.cend(), i) != params.used_features.cend()) {
            // Don't re-split on the same feature
            continue;
        }

        float remainder = calc_remainder(i);
        if (remainder < best_remainder) {
            best_index = i;
            best_remainder = remainder;
        }
    }

    float gain = calc_entropy_times_prob() - best_remainder;
    return std::make_pair(best_index, gain);
}

float Splitter::calc_remainder(unsigned int feature_index) const {
    signed int max_val = -1;
    std::vector<Sample>::const_iterator i = samples.cbegin();
    while (i != samples.cend()) {
        signed int cur_val = i->get_feature(feature_index);
        if (cur_val > max_val) {
            max_val = cur_val;
        }
        i++;
    }

    float remainder = 0.0f;
    for (signed int i = 0; i <= max_val; i++) {
        remainder += calc_entropy_times_prob(feature_index, i);
    }
    return remainder;
}

float Splitter::calc_entropy_times_prob() const {
    return calc_entropy_times_prob(static_cast<unsigned int>(-1), 0);
}

float Splitter::calc_entropy_times_prob(unsigned int feature_index, unsigned int feature_val) const {
    static std::vector<unsigned int> histogram;
    histogram.clear();
    unsigned int total = 0;

    build_histogram(histogram, total, feature_index, feature_val);

    float res = 0.0f;

    float total_inverse = 1.0f / total;
    std::vector<unsigned int>::const_iterator i = histogram.cbegin();
    while (i != histogram.cend()) {
        unsigned int count = *i;
        if (count) {
            float prob = count * total_inverse;
            res -= prob * std::log2(prob);
        }
        i++;
    }

    return res * total / samples.size();
}

unsigned int Splitter::get_frequent_result() const {
    static std::vector<unsigned int> histogram;
    histogram.clear();
    unsigned int total = 0;

    build_histogram(histogram, total, static_cast<unsigned int>(-1), 0);

    return std::max_element(histogram.cbegin(), histogram.cend()) - histogram.cbegin();
}

void Splitter::build_histogram(std::vector<unsigned int> &histogram, unsigned int &total, unsigned int feature_index, unsigned int feature_val) const {
    std::vector<Sample>::const_iterator i = samples.cbegin();
    while (i != samples.cend()) {
        const Sample &sample = *i;
        i++;

        if (feature_index == static_cast<unsigned int>(-1) || sample.get_feature(feature_index) == feature_val) {
            unsigned int result = sample.get_result();
            while (histogram.size() <= result) {
                histogram.push_back(0);
            }
            histogram[result]++;
            total++;
        }
    }
}

const DecisionNode *Splitter::split_on(unsigned int split_index, const TreeParams &params) const {
    signed int max_val = -1;
    std::vector<Sample>::const_iterator i = samples.cbegin();
    while (i != samples.cend()) {
        signed int cur_val = i->get_feature(split_index);
        if (cur_val > max_val) {
            max_val = cur_val;
        }
        i++;
    }

    Splitter *splitters = new Splitter[max_val + 1];
    i = samples.cbegin();
    while (i != samples.cend()) {
        splitters[i->get_feature(split_index)].add_sample(*i);
        i++;
    }

    DecisionNode *res = DecisionNode::create_branch(split_index);

    params.used_features.push_back(split_index);
    for (signed int i = 0; i <= max_val; i++) {
        res->add_child(splitters[i].create_tree(params));
    }
    params.used_features.pop_back();

    delete[] splitters;

    return res;
}

}