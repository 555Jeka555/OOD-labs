#ifndef LAB7_ISHAPEFACTORY_H
#define LAB7_ISHAPEFACTORY_H

#include "../Shape/IShape.h"

class IShapeFactory
{
public:
    virtual std::shared_ptr<IShape> CreateShape(const std::string & description) = 0;

    virtual ~IShapeFactory() = default;
};

#endif //LAB7_ISHAPEFACTORY_H
