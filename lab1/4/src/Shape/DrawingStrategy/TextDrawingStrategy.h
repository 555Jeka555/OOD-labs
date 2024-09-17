#ifndef INC_4_TEXTDRAWINGSTRATEGY_H
#define INC_4_TEXTDRAWINGSTRATEGY_H

#include <iostream>
#include <string>
#include <utility>
#include "IDrawingStrategy.h"

namespace shapes
{
    class TextDrawingStrategy : public IDrawingStrategy
    {
    public:
        TextDrawingStrategy(
                double leftTopX,
                double leftTopY,
                double size,
                std::string  text
        ) :
                m_leftTopX(leftTopX), m_leftTopY(leftTopY), m_size(size), m_text(std::move(text)) {}

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
                      << m_size << " "
                      << m_text << std::endl;
        }

    private:
        std::string m_type = "text";
        double m_leftTopX;
        double m_leftTopY;
        double m_size;
        std::string m_text;
    };
}

#endif //INC_4_TEXTDRAWINGSTRATEGY_H
