#ifndef LAB4_ISHAPEFACTORY_H
#define LAB4_ISHAPEFACTORY_H

#include "../Shape/Shape.h"

class IShapeFactory
{
public:
    virtual std::unique_ptr<Shape> CreateShape(const std::string & description) = 0;

    virtual ~IShapeFactory() = default;
};

#endif //LAB4_ISHAPEFACTORY_H
