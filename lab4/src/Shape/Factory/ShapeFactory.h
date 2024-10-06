#ifndef LAB4_SHAPEFACTORY_H
#define LAB4_SHAPEFACTORY_H

#include "IShapeFactory.h"

class ShapeFactory : public IShapeFactory
{
    std::unique_ptr<Shape> CreateShape(const std::string & description) override
    {

    }
};

#endif //LAB4_SHAPEFACTORY_H
