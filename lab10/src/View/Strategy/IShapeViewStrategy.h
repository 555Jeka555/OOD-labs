#ifndef LAB10_ISHAPEVIEWSTRATEGY_H
#define LAB10_ISHAPEVIEWSTRATEGY_H

#pragma once
#include "../../Canvas/ICanvas.h"

class IShapeViewStrategy
{
public:
    virtual void Draw(
            ICanvas &canvas,
            RectD frame,
            RGBAColor fillColor,
            RGBAColor lineColor,
            unsigned lineThickness
            ) = 0;

    virtual ~IShapeViewStrategy() = default;
};

#endif //LAB10_ISHAPEVIEWSTRATEGY_H
