#ifndef DT_TREEPARAMS_H
#define DT_TREEPARAMS_H

#include <vector>

namespace decision_tree {

struct TreeParams {
    unsigned int min_samples_to_split;
    float min_gain_to_split;

    mutable std::vector<unsigned int> used_features;
};

}

#endif // DT_TREEPARAMS_H
