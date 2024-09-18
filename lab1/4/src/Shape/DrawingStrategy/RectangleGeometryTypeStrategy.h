#ifndef INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H
#define INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "IGeometryTypeStrategy.h"

namespace shapes {
    class RectangleGeometryTypeStrategy : public IGeometryTypeStrategy
    {
    public:
        RectangleGeometryTypeStrategy(
                double leftTopX,
                double leftTopY,
                double width,
                double height
        ) :
            m_leftTopX(leftTopX), m_leftTopY(leftTopY), m_width(width), m_height(height) {}

        void Draw(gfx::ICanvas &canvas, uint32_t color) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_leftTopX, m_leftTopY);
            canvas.LineTo(m_leftTopX + m_width, m_leftTopY);
            canvas.LineTo(m_leftTopX + m_width, m_leftTopY + m_height);
            canvas.LineTo(m_leftTopX, m_leftTopY + m_height);
            canvas.LineTo(m_leftTopX, m_leftTopY);
        }

        void Move(double dx, double dy) override
        {
            m_leftTopX += dx;
            m_leftTopY += dy;
        }

        [[nodiscard]] std::string GetType() const override
        {
            return m_type;
        }

        [[nodiscard]] std::string ToString() const override
        {
            std::ostringstream oss;
            oss << m_leftTopX << " " << m_leftTopY << " " << m_width << " " << m_height;
            return oss.str();
        }

    private:
        static constexpr const std::string m_type = "rectangle";
        double m_leftTopX;
        double m_leftTopY;
        double m_width;
        double m_height;
    };
}

#endif //INC_4_RECTANGLEGEOMETRYTYPESTRATEGY_H
