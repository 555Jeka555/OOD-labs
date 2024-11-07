#pragma once

#include <cstdint>
#include "CommonTypes.h"
#include "Canvas/ICanvas.h"
#include <optional>
#include <memory>
#include <limits>
#include <functional>

using std::optional;

class IDrawable
{
public:
    virtual void Draw(gfx::ICanvas & canvas) const = 0;

    virtual ~IDrawable() = default;
};

class IStyle
{
public:
    virtual optional<bool> IsEnabled()const = 0;
    virtual void Enable(bool enable) = 0;

    virtual optional<RGBAColor> GetColor()const = 0;
    virtual void SetColor(RGBAColor color) = 0;

    virtual ~IStyle() = default;
};

class Style : public IStyle
{
public:
    explicit Style(optional<RGBAColor> color)
        :   m_color(color)
    {}

    [[nodiscard]] optional<bool> IsEnabled() const override
    {
        return m_enabled;
    }

    void Enable(bool enable) override
    {
        m_enabled = enable;
    }

    [[nodiscard]] optional<RGBAColor> GetColor() const override
    {
        return m_color;
    }

    void SetColor(RGBAColor color) override
    {
        m_color = color;
    }
private:
    optional<bool> m_enabled = std::nullopt;
    optional<RGBAColor> m_color = std::nullopt;
};

class IGroupShape;

class IShape : public IDrawable
{
public:
    virtual RectD GetFrame()const = 0;
    virtual void SetFrame(const RectD & rect) = 0;

    virtual IStyle & GetOutlineStyle() = 0;
    virtual const IStyle & GetOutlineStyle()const = 0;

    virtual IStyle & GetFillStyle() = 0;
    virtual const IStyle & GetFillStyle()const = 0;

    virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
    virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

    virtual ~IShape() = default;
};

class IShapes
{
public:
    virtual size_t GetShapesCount()const = 0;
    virtual void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
    virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const = 0;
    virtual void RemoveShapeAtIndex(size_t index) = 0;

    virtual ~IShapes() = default;
};

class IGroupShape : public IShape, public IShapes
{
public:
    virtual ~IGroupShape() = default;
};

typedef std::function<void(gfx::ICanvas & canvas, const IShape & shape)> DrawingStrategy;

class GroupShape : public IGroupShape
{
public:
    constexpr static std::string typeStart = "group_start";
    constexpr static std::string typeEnd = "group_end";

    GroupShape()
            : m_outlineStyle(0xFFFFFFFF),
              m_fillStyle(0xFFFFFFFF)
    {
    }

    RectD GetFrame() const override
    {
        return m_frame;
    }

    void SetFrame(const RectD & rect) override
    {
        m_frame = rect;
    }

    IStyle & GetOutlineStyle() override
    {
        return m_outlineStyle;
    }

    const IStyle & GetOutlineStyle() const override
    {
        return m_outlineStyle;
    }

    IStyle & GetFillStyle() override
    {
        return m_fillStyle;
    }

    const IStyle & GetFillStyle() const override
    {
        return m_fillStyle;
    }

    std::shared_ptr<IGroupShape> GetGroup() override
    {
        return nullptr;
    }

    std::shared_ptr<const IGroupShape> GetGroup() const override
    {
        return nullptr;
    }

    void Draw(gfx::ICanvas &canvas) const override
    {
        for (size_t i = 0; i < GetShapesCount(); ++i)
        {
            auto shape = GetShapeAtIndex(i);
            if (shape)
            {
                shape->Draw(canvas);
            }
        }
    }

    size_t GetShapesCount()const override
    {
        return m_shapes.size();
    }

    void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override
    {
        m_shapes.insert({position, shape});
    }

    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override
    {
        return m_shapes.at(index);
    }

    void RemoveShapeAtIndex(size_t index) override
    {
    }

private:
    std::unordered_map<size_t , std::shared_ptr<IShape>> m_shapes;
    RectD m_frame{};
    Style m_outlineStyle;
    Style m_fillStyle;
};


class ISlide : public IDrawable
{
public:
    virtual double GetWidth()const = 0;
    virtual double GetHeight()const = 0;

    [[nodiscard]] virtual IShapes & GetShapes() = 0;

    virtual ~ISlide() = default;
};

class IShapeFactory
{
public:
    virtual std::shared_ptr<IShape> CreateShape(const std::string & description) = 0;

    virtual ~IShapeFactory() = default;
};
