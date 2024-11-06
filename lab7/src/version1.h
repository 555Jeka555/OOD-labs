#pragma once

#include <iostream>
#include <sstream>
#include "CommonTypes.h"
#include "Canvas/ICanvas.h"
#include <memory>
#include <numeric>
#include <utility>
#include "ShapeLib.h"

namespace version1
{
    class Point
    {
    public:
        double x = 0;
        double y = 0;
    };

    class Shape : public IShape
    {
    public:
        Shape(Style outlineStyle, Style fillStyle)
            : m_outlineStyle(std::move(outlineStyle)), m_fillStyle(std::move(fillStyle)) {}

        RectD GetFrame() override
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

    private:
        RectD m_frame{};
        Style m_outlineStyle;
        Style m_fillStyle;
    };

    class Rectangle : public Shape
    {
    public:
        constexpr static std::string type = "rectangle";

        Rectangle(Style outlineStyle, Style fillStyle, Point leftTop, double width, double height)
            :   Shape(std::move(outlineStyle), std::move(fillStyle)),
                m_leftTop(leftTop),
                m_width(width),
                m_height(height)
            {}

        void Draw(gfx::ICanvas & canvas) const final override
        {
            canvas.SetLineColor(OptionalToUint32(GetOutlineStyle().GetColor()));
            canvas.BeginFill(OptionalToUint32(GetFillStyle().GetColor()));

            std::vector<std::pair<double, double>> vertices = {
                    {m_leftTop.x, m_leftTop.y},
                    {m_leftTop.x + m_width, m_leftTop.y},
                    {m_leftTop.x + m_width, m_leftTop.y + m_height},
                    {m_leftTop.x, m_leftTop.y + m_height}
            };

            canvas.DrawPolygon(vertices);

            canvas.EndFill();
        }

    private:
        Point m_leftTop;
        double m_width;
        double m_height;
    };

    class Ellipse : public Shape
    {
    public:
        constexpr static std::string type = "ellipse";

        Ellipse(Style outlineStyle, Style fillStyle, Point center, double radiusX, double radiusY)
            : Shape(std::move(outlineStyle), std::move(fillStyle)), m_center(center), m_radiusX(radiusX), m_radiusY(radiusY) {}

        void Draw(gfx::ICanvas & canvas) const final override
        {
            canvas.SetLineColor(OptionalToUint32(GetOutlineStyle().GetColor()));
            canvas.BeginFill(OptionalToUint32(GetFillStyle().GetColor()));

            canvas.DrawEllipse(m_center.x, m_center.y, m_radiusX, m_radiusY);

            canvas.EndFill();
        }

    private:
        Point m_center;
        double m_radiusX, m_radiusY;
    };

    class Triangle : public Shape
    {
    public:
        constexpr static std::string type = "triangle";

        Triangle(Style outlineStyle, Style fillStyle, Point point1, Point point2, Point point3)
            :   Shape(std::move(outlineStyle), std::move(fillStyle)),
                m_point1(point1),
                m_point2(point2),
                m_point3(point3)
                {}

        void Draw(gfx::ICanvas & canvas) const final
        {
            canvas.SetLineColor(OptionalToUint32(GetOutlineStyle().GetColor()));
            canvas.BeginFill(OptionalToUint32(GetFillStyle().GetColor()));

            std::vector<std::pair<double, double>> vertices = {
                    {m_point1.x, m_point1.y},
                    {m_point2.x, m_point2.y},
                    {m_point3.x, m_point3.y}
            };

            canvas.DrawPolygon(vertices);

            canvas.EndFill();
        }
    private:
        Point m_point1;
        Point m_point2;
        Point m_point3;
    };

    class Slide : public ISlide
    {
    public:
        explicit Slide(const GroupShape& shapes)
            :   m_background(0xFFFFFFFF),
                m_shapes(shapes)
        {
        }

        double GetWidth() const override
        {
            return 800;
        }

        double GetHeight() const override
        {
            return 600;
        }

        [[nodiscard]] IShapes & GetShapes() override
        {
            return m_shapes;
        }

        size_t GetShapesCount() const
        {
            return m_shapes.GetShapesCount();
        }

        std::shared_ptr<IShape> GetShapeAtIndex(size_t index)
        {
            return m_shapes.GetShapeAtIndex(index);
        }

        void RemoveShapeAtIndex(size_t index)
        {
            m_shapes.RemoveShapeAtIndex(index);
        }

        RGBAColor GetBackgroundColor() const
        {
            return m_background;
        }

        void SetBackgroundColor(RGBAColor color)
        {
            m_background = color;
        }

        void Draw(gfx::ICanvas & canvas) const override
        {
            for (size_t i = 0; i < GetShapesCount(); ++i)
            {
                auto shape = m_shapes.GetShapeAtIndex(i);
                if (shape)
                {
                    shape->Draw(canvas);
                }
            }
        }

    private:
        GroupShape m_shapes;
        RGBAColor m_background;
    };

    class ShapeFactory : public IShapeFactory
    {
    public:
        std::shared_ptr<IShape> CreateShape(const std::string & description) override
        {
            std::istringstream iss(description);

            std::string shapeType;
            iss >> shapeType;

            std::string colorOutlineStr;
            uint32_t colorOutline;
            iss >> colorOutlineStr;
            if (colorOutlineStr[0] == '#') {
                colorOutlineStr.erase(0, 1);
                std::stringstream ss;
                ss << std::hex << colorOutlineStr;
                ss >> colorOutline;
            }

            std::string colorFillStr;
            uint32_t colorFill;
            iss >> colorFillStr;
            if (colorFillStr[0] == '#') {
                colorFillStr.erase(0, 1);
                std::stringstream ss;
                ss << std::hex << colorFillStr;
                ss >> colorFill;
            }

            if (shapeType == Triangle::type)
            {
                return ShapeFactory::CreateTriangle(colorOutline, colorFill, iss);
            }
            else if (shapeType == Ellipse::type)
            {
                return ShapeFactory::CreateEllipse(colorOutline, colorFill, iss);
            }
            else if (shapeType == Rectangle::type)
            {
                return ShapeFactory::CreateRectangle(colorOutline, colorFill, iss);
            }

            throw std::invalid_argument("Unknown shape type");
        }

    private:
        static std::shared_ptr<Triangle> CreateTriangle(
                uint32_t colorOutline,
                uint32_t colorFill,
                std::istringstream& iss
                )
        {
            std::string pointX1Str;
            std::string pointY1Str;
            std::string pointX2Str;
            std::string pointY2Str;
            std::string pointX3Str;
            std::string pointY3Str;

            iss >> pointX1Str >> pointY1Str >> pointX2Str >> pointY2Str >> pointX3Str >> pointY3Str;

            Point point1(std::stod(pointX1Str), std::stod(pointY1Str));
            Point point2(std::stod(pointX2Str), std::stod(pointY2Str));
            Point point3(std::stod(pointX3Str), std::stod(pointY3Str));

            Style outlineStyle = Style(colorOutline);
            Style fillStyle = Style(colorFill);

            return std::make_shared<Triangle>(outlineStyle, fillStyle, point1, point2, point3);
        }

        static std::shared_ptr<Ellipse> CreateEllipse(
                uint32_t colorOutline,
                uint32_t colorFill,
                std::istringstream& iss
                )
        {
            std::string centerX1Str;
            std::string centerY1Str;
            std::string horizontalRadiusStr;
            std::string verticalRadiusStr;

            iss >> centerX1Str >> centerY1Str >> horizontalRadiusStr >> verticalRadiusStr;

            Point center(std::stod(centerX1Str), std::stod(centerY1Str));

            Style outlineStyle = Style(colorOutline);
            Style fillStyle = Style(colorFill);

            return std::make_shared<Ellipse>(
                    outlineStyle,
                    fillStyle,
                    center,
                    std::stod(horizontalRadiusStr),
                    std::stod(verticalRadiusStr)
            );
        }

        static std::shared_ptr<Rectangle> CreateRectangle(
                uint32_t colorOutline,
                uint32_t colorFill,
                std::istringstream& iss
                )
        {
            std::string leftTopX1Str;
            std::string leftTopY1Str;
            std::string widthStr;
            std::string heightStr;

            iss >> leftTopX1Str >> leftTopY1Str >> widthStr >> heightStr;

            Point leftTop(std::stod(leftTopX1Str), std::stod(leftTopY1Str));

            Style outlineStyle = Style(colorOutline);
            Style fillStyle = Style(colorFill);

            return std::make_shared<Rectangle>(
                    outlineStyle,
                    fillStyle,
                    leftTop,
                    std::stod(widthStr),
                    std::stod(heightStr)
            );
        }
    };

    class SlideService
    {
    public:
        explicit SlideService(IShapeFactory& shapeFactory)
            :   m_shapeFactory(shapeFactory)
        {}

        void CreateSlide(std::istream & inputData)
        {
            std::string line;

            auto firstGroup = GroupShape();

            int i = 0;
            while (getline(inputData, line))
            {
                auto shape = m_shapeFactory.CreateShape(line);
                if (shape)
                {
                    firstGroup.InsertShape(shape, i);
                    i++;
                }
            }
            m_currentSlide = std::make_unique<Slide>(firstGroup);
        }

        void DrawSlide(gfx::ICanvas & canvas)
        {
            if (m_currentSlide != nullptr)
            {
                m_currentSlide->Draw(canvas);
            }
        }

    private:
        IShapeFactory & m_shapeFactory;
        std::unique_ptr<ISlide> m_currentSlide;
    };
}
