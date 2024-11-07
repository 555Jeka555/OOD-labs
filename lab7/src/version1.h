#pragma once

#include <iostream>
#include <sstream>
#include "CommonTypes.h"
#include "Canvas/ICanvas.h"
#include <memory>
#include <numeric>
#include <utility>
#include "ShapeLib.h"

namespace version1 {
    class Point {
    public:
        double x = 0;
        double y = 0;
    };

    class Shape : public IShape {
    public:
        Shape(const RectD &frame,
              std::unique_ptr<IStyle> outlineStyle,
              std::unique_ptr<IStyle> fillStyle
        )
            :    m_frame(frame),
                m_outlineStyle(std::move(outlineStyle)),
                m_fillStyle(std::move(fillStyle))
        {
        }

        RectD GetFrame() const override
        {
            return m_frame;
        }

        void SetFrame(const RectD &rect) override {
            m_frame = rect;
        }

        IStyle &GetOutlineStyle() override {
            return *m_outlineStyle;
        }

        const IStyle &GetOutlineStyle() const override {
            return *m_outlineStyle;
        }

        IStyle &GetFillStyle() override {
            return *m_fillStyle;
        }

        const IStyle &GetFillStyle() const override {
            return *m_fillStyle;
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
        std::unique_ptr<IStyle> m_outlineStyle;
        std::unique_ptr<IStyle> m_fillStyle;
    };

    class Rectangle : public Shape {
    public:
        constexpr static std::string type = "rectangle";

        Rectangle(
                const RectD &frame,
                std::unique_ptr<IStyle> outlineStyle,
                std::unique_ptr<IStyle> fillStyle
        ): Shape(frame, std::move(outlineStyle), std::move(fillStyle))
        {
        }

        void Draw(gfx::ICanvas &canvas) const final override {
            const IStyle &outlineStyle = GetOutlineStyle();
            const IStyle &fillStyle = GetFillStyle();

            if (fillStyle.IsEnabled() && fillStyle.GetColor().has_value())
            {
                canvas.BeginFill(fillStyle.GetColor().value());
            }

            if (outlineStyle.IsEnabled() && outlineStyle.GetColor().has_value())
            {
                canvas.SetLineColor(outlineStyle.GetColor().value());
            }
            else
            {
                canvas.SetLineColor({});
            }

            auto [left, top, width, height] = GetFrame();

            const std::vector<std::pair<double, double>> vertices = {
                    {left, top},
                    {left + width, top},
                    {left + width, top + height},
                    {left, top + height}
            };
            canvas.DrawPolygon(vertices);

            canvas.EndFill();
        }
    };

    class Ellipse : public Shape {
    public:
        constexpr static std::string type = "ellipse";

        Ellipse(const RectD &frame,
                std::unique_ptr<IStyle> outlineStyle,
                std::unique_ptr<IStyle> fillStyle
        )
            : Shape(frame, std::move(outlineStyle), std::move(fillStyle))
        {
        }

        void Draw(gfx::ICanvas &canvas) const override
        {
            const IStyle &outlineStyle = GetOutlineStyle();
            const IStyle &fillStyle = GetFillStyle();

            if (fillStyle.IsEnabled() && fillStyle.GetColor().has_value())
            {
                canvas.BeginFill(fillStyle.GetColor().value());
            }

            if (outlineStyle.IsEnabled() && outlineStyle.GetColor().has_value())
            {
                canvas.SetLineColor(outlineStyle.GetColor().value());
            }
            else
            {
                canvas.SetLineColor(0xFFFFFFFF);
            }

            auto frame = GetFrame();
            double cx = frame.left + frame.width / 2;
            const double cy = frame.top + frame.height / 2;
            const double rx = frame.width / 2;
            const double ry = frame.height / 2;
            canvas.DrawEllipse(cx, cy, rx, ry);

            canvas.EndFill();
        }
    };

    class Triangle : public Shape {
    public:
        constexpr static std::string type = "triangle";

        Triangle(const RectD &frame,
                std::unique_ptr<IStyle> outlineStyle,
                std::unique_ptr<IStyle> fillStyle
        )
            : Shape(frame, std::move(outlineStyle), std::move(fillStyle))
        {
        }

        void Draw(gfx::ICanvas &canvas) const final {
            const IStyle &outlineStyle = GetOutlineStyle();
            const IStyle &fillStyle = GetFillStyle();

            if (fillStyle.IsEnabled() && fillStyle.GetColor().has_value())
            {
                canvas.BeginFill(fillStyle.GetColor().value());
            }

            if (outlineStyle.IsEnabled() && outlineStyle.GetColor().has_value())
            {
                canvas.SetLineColor(outlineStyle.GetColor().value());
            }
            else
            {
                canvas.SetLineColor({});
            }

            const auto [left, top, width, height] = GetFrame();

            const std::vector<std::pair<double, double>> vertices = {
                    {left + width / 2, top},
                    {left, top + height},
                    {left + width, top + height}
            };

            canvas.DrawPolygon(vertices);

            canvas.EndFill();
        }
    };

    class Slide : public ISlide {
    public:
        explicit Slide(const std::shared_ptr<GroupShape> &shapes)
                : m_background(0xFFFFFFFF),
                  m_shapes(shapes) {
        }

        double GetWidth() const override {
            return 800;
        }

        double GetHeight() const override {
            return 600;
        }

        [[nodiscard]] IShapes &GetShapes() override {
            return *m_shapes;
        }

        size_t GetShapesCount() const {
            return m_shapes->GetShapesCount();
        }

        std::shared_ptr<IShape> GetShapeAtIndex(size_t index) {
            return m_shapes->GetShapeAtIndex(index);
        }

        void RemoveShapeAtIndex(size_t index) {
            m_shapes->RemoveShapeAtIndex(index);
        }

        RGBAColor GetBackgroundColor() const {
            return m_background;
        }

        void SetBackgroundColor(RGBAColor color) {
            m_background = color;
        }

        void Draw(gfx::ICanvas &canvas) const override {
            m_shapes->Draw(canvas);
        }

    private:
        std::shared_ptr<GroupShape> m_shapes;
        RGBAColor m_background;
    };

    class ShapeFactory : public IShapeFactory {
    public:
        std::shared_ptr<IShape> CreateShape(const std::string &description) override {
            std::istringstream iss(description);

            std::string shapeType;
            iss >> shapeType;

            auto outlineStyle = ParseStyle(iss);
            auto fillStyle = ParseStyle(iss);

            if (shapeType == Triangle::type) {
                return ShapeFactory::CreateTriangle(iss, std::move(outlineStyle), std::move(fillStyle));
            } else if (shapeType == Ellipse::type) {
                return ShapeFactory::CreateEllipse(iss, std::move(outlineStyle), std::move(fillStyle));
            } else if (shapeType == Rectangle::type) {
                return ShapeFactory::CreateRectangle(iss, std::move(outlineStyle), std::move(fillStyle));
            }

            throw std::invalid_argument("Unknown shape type");
        }

    private:
        static std::shared_ptr<Triangle> CreateTriangle(
                std::istringstream &iss,
                std::unique_ptr<IStyle> outlineStyle,
                std::unique_ptr<IStyle> fillStyle
        ) {
            const auto rect = ParseRect(iss);

            return std::make_unique<Triangle>(rect, std::move(outlineStyle), std::move(fillStyle));
        }

        static std::shared_ptr<Ellipse> CreateEllipse(
                std::istringstream &iss,
                std::unique_ptr<IStyle> outlineStyle,
                std::unique_ptr<IStyle> fillStyle
        ) {
            const auto rect = ParseRect(iss);

            return std::make_unique<Ellipse>(rect, std::move(outlineStyle), std::move(fillStyle));
        }

        static std::shared_ptr<Rectangle> CreateRectangle(
                std::istringstream &iss,
                std::unique_ptr<IStyle> outlineStyle,
                std::unique_ptr<IStyle> fillStyle
        ) {
            const auto rect = ParseRect(iss);

            return std::make_unique<Rectangle>(rect, std::move(outlineStyle), std::move(fillStyle));

        }

        static std::unique_ptr<IStyle> ParseStyle(std::istringstream &iss)
        {
            std::string colorStr;
            RGBAColor color;

            if (!(iss >> colorStr) || !ParseColor(colorStr, color))
            {
                return std::make_unique<Style>(std::nullopt);
            }

            auto style = std::make_unique<Style>(color);
            style->Enable(true);

            return style;
        }


        static bool ParseColor(std::string colorStr, RGBAColor &color)
        {
            if (colorStr.size() != 7 || colorStr[0] != '#')
            {
                return false;
            }
            std::stringstream ss;
            ss << std::hex << colorStr.append("FF").substr(1);

            if (!(ss >> color))
            {
                return false;
            }

            return ss.eof();
        }

        static RectD ParseRect(std::istringstream & iss)
        {
            double left, top, width, height;

            if (!(iss >> left >> top >> width >> height))
            {
                throw std::invalid_argument("Invalid rect parameters");
            }

            if (width < 0 || height < 0)
            {
                throw std::invalid_argument("Width and height must be non-negative");
            }

            return {left, top, width, height};
        }
    };

    class SlideService {
    public:
        explicit SlideService(IShapeFactory &shapeFactory)
                : m_shapeFactory(shapeFactory) {}

        void CreateSlide(std::istream &inputData) {
            std::string line;
            auto firstGroup = std::make_shared<GroupShape>();
            std::vector<std::shared_ptr<GroupShape>> groupStack;
            groupStack.push_back(firstGroup);
            int i = 0;

            while (getline(inputData, line)) {
                if (IsStartOrEndCreateGroup(line, groupStack, i)) {
                    continue;
                }

                auto shape = m_shapeFactory.CreateShape(line);
                if (shape) {
                    groupStack.back()->InsertShape(shape, groupStack.back()->GetShapesCount());
                }
            }

            m_currentSlide = std::make_unique<Slide>(firstGroup);
        }

        void DrawSlide(gfx::ICanvas &canvas) {
            if (m_currentSlide != nullptr) {
                m_currentSlide->Draw(canvas);
            }
        }

        static bool IsStartOrEndCreateGroup(
                const std::string &line,
                std::vector<std::shared_ptr<GroupShape>> &groupStack,
                int &i) {
            if (line == GroupShape::typeStart) {
                auto newGroup = std::make_shared<GroupShape>();
                groupStack.back()->InsertShape(std::static_pointer_cast<IShape>(newGroup),
                                               groupStack.back()->GetShapesCount());
                groupStack.push_back(newGroup);
                return true;
            }

            if (line == GroupShape::typeEnd) {
                if (groupStack.size() > 1) {
                    groupStack.pop_back();
                }
                return true;
            }

            return false;
        }


    private:
        IShapeFactory &m_shapeFactory;
        std::unique_ptr<ISlide> m_currentSlide;
    };
}
