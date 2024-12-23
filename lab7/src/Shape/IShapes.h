#ifndef LAB7_ISHAPES_H
#define LAB7_ISHAPES_H

#include <cstdint>
#include <memory>
#include <limits>
#include "IShape.h"

class IShape;

class IShapes
{
public:
    virtual size_t GetShapesCount()const = 0;
    virtual void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
    virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const = 0;
    virtual void RemoveShapeAtIndex(size_t index) = 0;

    virtual ~IShapes() = default;
};

#endif //LAB7_ISHAPES_H
