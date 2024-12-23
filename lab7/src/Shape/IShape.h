#ifndef LAB7_ISHAPE_H
#define LAB7_ISHAPE_H

#include <memory>
#include <optional>
#include "../CommonTypes.h"
#include "../IDrawable.h"
#include "Style/IStyle.h"
#include "IShapes.h"

class IGroupShape;

// TODO unbale_shared_from_this
class IShape : public IDrawable
{
public:
    virtual std::optional<RectD> GetFrame()const = 0;
    virtual void SetFrame(const std::optional<RectD> & rect) = 0;

    virtual IStyle & GetOutlineStyle() = 0;
    virtual const IStyle & GetOutlineStyle()const = 0;

    virtual IStyle & GetFillStyle() = 0;
    virtual const IStyle & GetFillStyle()const = 0;

    virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
    virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

    virtual ~IShape() = default;
};

class IGroupShape : public IShape, public IShapes
{
public:
    virtual ~IGroupShape() = default;
};

#endif //LAB7_ISHAPE_H
