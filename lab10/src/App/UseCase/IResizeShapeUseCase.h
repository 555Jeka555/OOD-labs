#ifndef LAB10_IRESIZESHAPEUSECASE_H
#define LAB10_IRESIZESHAPEUSECASE_H

#pragma once
#include "../../Common/Point.h"

class IResizeShapeUseCase
{
public:

    virtual void Resize(const Point& offset, DirectionPoint directionPoint) = 0;

    virtual void Execute() = 0;

    ~IResizeShapeUseCase() = default;
};

#endif //LAB10_IRESIZESHAPEUSECASE_H
