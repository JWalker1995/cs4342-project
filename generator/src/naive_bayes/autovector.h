#ifndef AUTOVECTOR_H
#define AUTOVECTOR_H

#include <assert.h>
#include <vector>

template <typename ElementType>
class AutoVector : public std::vector<ElementType>{
public:
    ElementType &operator[](unsigned int index) {
        if (index >= std::vector<ElementType>::size()) {
            std::vector<ElementType>::resize(index + 1);
        }
        return std::vector<ElementType>::operator[](index);
    }

    const ElementType &operator[](unsigned int index) const {
        assert(index < std::vector<ElementType>::size());
        return std::vector<ElementType>::operator[](index);
    }
};

#endif // AUTOVECTOR_H
