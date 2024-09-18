#ifndef INC_4_TEXTGEOMETRYTYPESTRATEGY_H
#define INC_4_TEXTGEOMETRYTYPESTRATEGY_H

#include <iostream>
#include <string>
#include <utility>
#include "IGeometryTypeStrategy.h"

namespace shapes
{
    class TextGeometryTypeStrategy : public IGeometryTypeStrategy
    {
    public:
        TextGeometryTypeStrategy(
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

        [[nodiscard]] std::string ToString() const override
        {
            std::ostringstream oss;
            oss << m_leftTopX << " " << m_leftTopY << " " << m_size << " " << m_text;
            return oss.str();
        }

    private:
        static constexpr const std::string m_type = "text";
        double m_leftTopX;
        double m_leftTopY;
        double m_size;
        std::string m_text;
    };
}

#endif //INC_4_TEXTGEOMETRYTYPESTRATEGY_H
