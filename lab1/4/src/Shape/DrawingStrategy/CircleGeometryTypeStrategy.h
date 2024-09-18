#ifndef INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H
#define INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include "IGeometryTypeStrategy.h"

namespace shapes
{
    class CircleGeometryTypeStrategy : public IGeometryTypeStrategy
    {
    public:
        CircleGeometryTypeStrategy(
                double centerX,
                double centerY,
                double radius
        ) :
                m_centerX(centerX), m_centerY(centerY), m_radius(radius) {}

        void Draw(ICanvas &canvas, uint32_t color) const override {
            // Реализация рисования круга (если требуется)
        }

        void Move(double dx, double dy) override
        {
            m_centerX += dx;
            m_centerY += dy;
        }

        [[nodiscard]] std::string GetType() const override
        {
            return m_type;
        }

        [[nodiscard]] std::string ToString() const override
        {
            std::ostringstream oss;
            oss << m_centerX << " " << m_centerY << " " << m_radius;
            return oss.str();
        }

    private:
        static constexpr const std::string m_type = "circle";
        double m_centerX;
        double m_centerY;
        double m_radius;
    };
}

#endif //INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H