#include "builder.h"

namespace naive_bayes {

void Builder::add_sample(Sample sample) {
    // Build an array of counts with these dimensions:
    // counts[result][feature_index][feature_value]
    // Example:
    // counts["up"]["outlook"]["overcast"] == 12
    
    // result_counts is the counts of values for each feature
    std::array<AutoVector<unsigned int>, num_columns> &result_counts = counts[sample.get_result()];
    
    // Add counts for each feature instance in the sample
    for (unsigned int i = 0; i < num_columns; i++) {
        result_counts[i][sample.get_feature(i)]++;
    }
    
    // Increment the row counter
    rows++;
}

std::string Builder::to_js_code() const {
    std::string res;

    res += "function(features) {\n";
    res += "let data = [\n";

    // JSON-ify the counts array
    AutoVector<std::array<AutoVector<unsigned int>, num_columns>>::const_iterator i = counts.cbegin();
    while (i != counts.cend()) {
        res += "[";
        for (unsigned int j = 0; j < num_columns; j++) {
            res += "[";
            const AutoVector<unsigned int> &histogram = (*i)[j];
            AutoVector<unsigned int>::const_iterator k = histogram.cbegin();
            while (k != histogram.cend()) {
                res += std::to_string(*k) + ", ";
                k++;
            }
            res += "], ";
        }
        res += "],\n";
        i++;
    }
    res += "];\n";

    // Calculate the probability for each result
    res += "return data.map(function(result, i) {\n";
    res += "    let total = result[" + std::to_string(Sample::num_features) + "][i];\n";
    res += "    let prob = total / " + std::to_string(rows) + ";\n";
    res += "    result.forEach(function(histogram, j) {\n";
    res += "        if (j == " + std::to_string(Sample::num_features) + ") {return;}\n";
    res += "        prob *= histogram[features[j]] / total;\n";
    res += "    });\n";
    res += "    return prob;\n";
    res += "});\n";
    res += "}";
    
    return res;
}

}