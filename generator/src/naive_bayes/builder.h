#ifndef NB_BUILDER_H
#define NB_BUILDER_H

#include <array>
#include <string>

#include "../sample.h"
#include "autovector.h"

namespace naive_bayes {

class Builder {
public:
    void add_sample(Sample sample);
    std::string to_js_code() const;
    
private:
    // Build an array of counts with these dimensions:
    // counts[result][feature_index][feature_value]
    // Example:
    // counts["up"]["outlook"]["overcast"] == 12
    AutoVector<std::array<AutoVector<unsigned int>, num_columns>> counts;
    unsigned int rows = 0;
};

}

#endif // NB_BUILDER_H