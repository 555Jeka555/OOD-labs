#ifndef INC_4_TRIANGLEGEOMETRYTYPESTRATEGY_H
#define INC_4_TRIANGLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "IGeometryTypeStrategy.h"

namespace shapes
{
    class TriangleGeometryTypeStrategy : public IGeometryTypeStrategy
    {
    public:
        TriangleGeometryTypeStrategy(
                double x1,
                double y1,
                double x2,
                double y2,
                double x3,
                double y3
        ) :
            m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_x3(x3), m_y3(y3) {}

        void Draw(gfx::ICanvas &canvas, uint32_t color) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_x1, m_y1);
            canvas.LineTo(m_x2, m_y2);
            canvas.LineTo(m_x3, m_y3);
            canvas.LineTo(m_x1, m_y1);
        }

        void Move(double dx, double dy) override
        {
            m_x1 += dx;
            m_y1 += dy;
            m_x2 += dx;
            m_y2 += dy;
            m_x3 += dx;
            m_y3 += dy;
        }

        [[nodiscard]] std::string GetType() const override
        {
            return m_type;
        }

        [[nodiscard]] std::string ToString() const override
        {
            std::ostringstream oss;
            oss << m_x1 << " "
                << m_y1 << " "
                << m_x2 << " "
                << m_y2 << " "
                << m_x3 << " "
                << m_y3;
            return oss.str();
        }

    private:
        static constexpr const std::string m_type = "triangle";
        double m_x1;
        double m_y1;
        double m_x2;
        double m_y2;
        double m_x3;
        double m_y3;
    };
}

#endif //INC_4_TRIANGLEGEOMETRYTYPESTRATEGY_H
