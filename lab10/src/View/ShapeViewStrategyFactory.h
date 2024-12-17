#ifndef LAB10_SHAPEVIEWSTRATEGYFACTORY_H
#define LAB10_SHAPEVIEWSTRATEGYFACTORY_H

#pragma once
#include "IShapeViewStrategyFactory.h"
#include "Strategy/EllipseViewStrategy.h"
#include "Strategy/RectangleViewStrategy.h"
#include "Strategy/TriangleViewStrategy.h"

class ShapeViewStrategyFactory : public IShapeViewStrategyFactory
{
public:
    std::shared_ptr<IShapeViewStrategy> Create(ShapeType shapeType) override
    {
        switch (shapeType)
        {
            case ShapeType::RECTANGLE:
                return std::make_shared<RectangleViewStrategy>();
            case ShapeType::TRIANGLE:
                return std::make_shared<TriangleViewStrategy>();
            case ShapeType::ELLIPSE:
                return std::make_shared<EllipseViewStrategy>();
            default:
                break;
        }

        return nullptr;
    }

};

#endif //LAB10_SHAPEVIEWSTRATEGYFACTORY_H
