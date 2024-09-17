#ifndef INC_4_RECTANGLEDRAWINGSTRATEGY_H
#define INC_4_RECTANGLEDRAWINGSTRATEGY_H

#include <iostream>
#include <string>
#include "IDrawingStrategy.h"

namespace shapes {
    class RectangleDrawingStrategy : public IDrawingStrategy
    {
    public:
        RectangleDrawingStrategy(
                double leftTopX,
                double leftTopY,
                double width,
                double height
        ) :
                m_leftTopX(leftTopX), m_leftTopY(leftTopY), m_width(width), m_height(height) {}

        void Draw(ICanvas &canvas, uint32_t color) const override
        {

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

        void Display(const std::string &id, uint32_t color) const override
        {
            std::cout << m_type << " "
                      << id << " "
                      << "#" << std::hex << std::setw(6) << std::setfill('0') << color << " "
                      << m_leftTopX << " "
                      << m_leftTopY << " "
                      << m_width << " "
                      << m_height << std::endl;
        }

    private:
        std::string m_type = "rectangle";
        double m_leftTopX;
        double m_leftTopY;
        double m_width;
        double m_height;
    };
}

#endif //INC_4_RECTANGLEDRAWINGSTRATEGY_H
