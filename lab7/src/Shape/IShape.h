#ifndef LAB7_ISHAPE_H
#define LAB7_ISHAPE_H

#include <memory>
#include "../CommonTypes.h"
#include "../IDrawable.h"
#include "Style/IStyle.h"

class IShape : public IDrawable
{
public:
    virtual RectD GetFrame()const = 0;
    virtual void SetFrame(const RectD & rect) = 0;

    virtual IStyle & GetOutlineStyle() = 0;
    virtual const IStyle & GetOutlineStyle()const = 0;

    virtual IStyle & GetFillStyle() = 0;
    virtual const IStyle & GetFillStyle()const = 0;

    virtual ~IShape() = default;
};

#endif //LAB7_ISHAPE_H
