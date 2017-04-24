#ifndef TREEPARAMS_H
#define TREEPARAMS_H

#include <vector>

struct TreeParams {
    unsigned int min_samples_to_split;
    float min_gain_to_split;

    mutable std::vector<unsigned int> used_features;
};

#endif // TREEPARAMS_H
