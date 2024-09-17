#ifndef INC_4_LINEDRAWINGSTRATEGY_H
#define INC_4_LINEDRAWINGSTRATEGY_H

#include <iostream>
#include <string>
#include "IDrawingStrategy.h"

namespace shapes {
    class LineDrawingStrategy : public IDrawingStrategy
    {
    public:
        LineDrawingStrategy(
                double x1,
                double y1,
                double x2,
                double y2
        ) :
            m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2){}

        void Draw(ICanvas &canvas, uint32_t color) const override
        {

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

        void Display(const std::string &id, uint32_t color) const override
        {
            std::cout << m_type << " "
                      << id << " "
                      << "#" << std::hex << std::setw(6) << std::setfill('0') << color << " "
                      << m_x1 << " "
                      << m_y1 << " "
                      << m_x2 << " "
                      << m_y2 << std::endl;
        }

    private:
        std::string m_type = "line";
        double m_x1;
        double m_y1;
        double m_x2;
        double m_y2;
    };
}

#endif //INC_4_LINEDRAWINGSTRATEGY_H
