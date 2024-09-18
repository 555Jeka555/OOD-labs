#ifndef INC_4_LINEGEOMETRYTYPESTRATEGY_H
#define INC_4_LINEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "IGeometryTypeStrategy.h"

namespace shapes
{
    class LineGeometryTypeStrategy : public IGeometryTypeStrategy
    {
    public:
        LineGeometryTypeStrategy(
                double x1,
                double y1,
                double x2,
                double y2
        ) :
            m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2){}

        void Draw(ICanvas &canvas, uint32_t color) const override
        {
            canvas.SetColor(color);
            canvas.MoveTo(m_x1, m_y1);
            canvas.LineTo(m_x2, m_y2);
        }

        void Move(double dx, double dy) override
        {
            m_x1 += dx;
            m_y1 += dy;
            m_x2 += dx;
            m_y2 += dy;
        }

        [[nodiscard]] std::string GetType() const override
        {
            return m_type;
        }

        [[nodiscard]] std::string ToString() const override
        {
            std::ostringstream oss;
            oss << m_x1 << " " << m_y1 << " " << m_x2 << " " << m_y2;
            return oss.str();
        }

    private:
        static constexpr const std::string m_type = "line";
        double m_x1;
        double m_y1;
        double m_x2;
        double m_y2;
    };
}

#endif //INC_4_LINEGEOMETRYTYPESTRATEGY_H
