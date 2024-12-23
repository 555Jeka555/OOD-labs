#ifndef LAB10_IMOVESHAPEUSECASE_H
#define LAB10_IMOVESHAPEUSECASE_H

#pragma once
#include "../../Common/Point.h"

class IMoveShapeUseCase
{
public:

    virtual void Move(const Point & offset) = 0;

    virtual void Execute() = 0;

    ~IMoveShapeUseCase() = default;
};

#endif //LAB10_IMOVESHAPEUSECASE_H
