#include <iostream>

#include "treeparams.h"
#include "sample.h"
#include "splitter.h"
#include "decisionnode.h"

int main() {
    TreeParams params;
    params.min_samples_to_split = 1;
    params.min_gain_to_split = 0.01f; // Must be greater than zero

    std::cout << "Enter [num_features] [num_samples]" << std::endl;

    std::cin >> Sample::num_features;

    unsigned int num_samples;
    std::cin >> num_samples;

    Splitter root;

    for (unsigned int i = 0; i < num_samples; i++) {
        std::cout << "Enter sample " << (i + 1) << ":" << std::endl;

        Sample sample;

        for (unsigned int j = 0; j < Sample::num_features; j++) {
            unsigned int feature;
            std::cin >> feature;
            sample.set_feature(j, feature);
        }

        unsigned int result;
        std::cin >> result;
        sample.set_result(result);

        root.add_sample(sample);
    }

    std::cout << "Creating decision tree..." << std::endl;

    const DecisionNode *decision_tree = root.create_tree(params);
    std::cout << decision_tree->to_string() << std::endl;

    while (true) {
        std::cout << "Enter a sample to classify:" << std::endl;

        Sample sample;

        for (unsigned int j = 0; j < Sample::num_features; j++) {
            unsigned int feature;
            std::cin >> feature;
            sample.set_feature(j, feature);
        }

        std::cout << "Classification = " << decision_tree->classify(sample) << std::endl;
    }

    return 0;
}
