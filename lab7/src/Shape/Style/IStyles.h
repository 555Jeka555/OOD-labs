#ifndef LAB7_ISTYLES_H
#define LAB7_ISTYLES_H

#include <cstdint>
#include <limits>
#include <memory>
#include "IStyle.h"

class IStyles
{
public:
    virtual void InsertStyle(IStyle & style, size_t position = std::numeric_limits<size_t>::max()) = 0;
    virtual void RemoveShapeAtIndex(size_t index) = 0;

    virtual ~IStyles() = default;
};

#endif //LAB7_ISTYLES_H
