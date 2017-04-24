#ifndef SAMPLE_H
#define SAMPLE_H

#include <assert.h>

class Sample {
public:
    Sample()
        : features(new unsigned int[num_features + 1])
    {
        assert(num_features);
    }

    void set_feature(unsigned int index, unsigned int value) {
        assert(index < num_features);
        features[index] = value;
    }
    void set_result(unsigned int value) {
        features[num_features] = value;
    }

    unsigned int get_feature(unsigned int index) const {
        assert(index < num_features);
        return features[index];
    }
    unsigned int get_result() const {
        return features[num_features];
    }

    static unsigned int num_features;

private:
    unsigned int *features;
};

#endif // SAMPLE_H
