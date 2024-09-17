#ifndef INC_4_SHAPE_H
#define INC_4_SHAPE_H

#include <iostream>
#include <string>
#include <cstdint>
#include <memory>
#include <utility>
#include "../Canvas/ICanvas.h"
#include "../Shape/DrawingStrategy/IDrawingStrategy.h"

namespace shapes
{
    class Shape
    {
    public:
        Shape(std::string id, uint32_t color, std::unique_ptr<IDrawingStrategy> drawingStrategy) :
                m_id(std::move(id)), m_color(color), m_drawingStrategy(std::move(drawingStrategy))
        {}

        void Draw(ICanvas& canvas)
        {
            m_drawingStrategy->Draw(canvas, m_color);
        }

        void Move(double dx, double dy)
        {
            m_drawingStrategy->Move(dx, dy);
        }

        [[nodiscard]] std::string GetType() const
        {
            return m_drawingStrategy->GetType();
        }

        [[nodiscard]] std::string GetId() const {
            return m_id;
        }

        void SetColor(uint32_t mColor) {
            m_color = mColor;
        }

        void SetDrawingStrategy(const std::unique_ptr<IDrawingStrategy> drawingStrategy) {
            m_drawingStrategy.reset(drawingStrategy.get());
        }

        void Display()
        {
            m_drawingStrategy->Display(m_id, m_color);
        }

        ~Shape() = default;
    private:
        std::string m_id;
        uint32_t m_color;
        std::unique_ptr<IDrawingStrategy> m_drawingStrategy;
    };
}

#endif //INC_4_SHAPE_H
