#ifndef LAB10_IINSERTSHAPEUSECASE_H
#define LAB10_IINSERTSHAPEUSECASE_H

#pragma once
#include <cstddef>
#include "../../Common/ShapeType.h"

class IInsertShapeUseCase
{
public:

    virtual void Execute(size_t index, ShapeType shapeType) = 0;

    ~IInsertShapeUseCase() = default;
};

#endif //LAB10_IINSERTSHAPEUSECASE_H
