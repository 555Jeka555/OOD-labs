#ifndef LAB10_ISHAPEVIEWSTRATEGYFACTORY_H
#define LAB10_ISHAPEVIEWSTRATEGYFACTORY_H

#pragma once
#include <memory>
#include "Strategy/IShapeViewStrategy.h"
#include "../Common/ShapeType.h"

class IShapeViewStrategyFactory
{
public:
    virtual std::shared_ptr<IShapeViewStrategy> Create(ShapeType shapeType) = 0;

    ~IShapeViewStrategyFactory() = default;
};

#endif //LAB10_ISHAPEVIEWSTRATEGYFACTORY_H
