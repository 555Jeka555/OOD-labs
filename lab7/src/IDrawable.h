#ifndef LAB7_IDRAWABLE_H
#define LAB7_IDRAWABLE_H

#include "Canvas/ICanvas.h"

class IDrawable
{
public:
    virtual void Draw(gfx::ICanvas & canvas) const = 0;

    virtual ~IDrawable() = default;
};

#endif //LAB7_IDRAWABLE_H
