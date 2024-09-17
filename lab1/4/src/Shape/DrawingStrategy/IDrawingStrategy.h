#ifndef INC_4_IDRAWINGSTRATEGY_H
#define INC_4_IDRAWINGSTRATEGY_H

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include "../../Canvas/ICanvas.h"

namespace shapes
{
    class IDrawingStrategy
    {
    public:
        virtual void Draw(ICanvas& canvas, uint32_t color) const = 0;

        virtual void Move(double dx, double dy) = 0;

        [[nodiscard]] virtual std::string GetType() const = 0;

        virtual void Display(const std::string& id, uint32_t color) const = 0;

        virtual ~IDrawingStrategy() = default;
    };
}
#endif //INC_4_IDRAWINGSTRATEGY_H
