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

        void Display(const std::string &id, uint32_t color) const override
        {
            std::cout << m_type << " "
                      << id << " "
                      << "#" << std::hex << std::setw(6) << std::setfill('0') << color << " "
                      << m_centerX << " "
                      << m_centerY << " "
                      << m_radius << std::endl;
        }

    private:
        std::string m_type = "circle";
        double m_centerX;
        double m_centerY;
        double m_radius;
    };
}

#endif //INC_4_CIRCLEGEOMETRYTYPESTRATEGY_H
