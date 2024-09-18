#ifndef INC_4_IGEOMETRYTYPESTRATEGY_H
#define INC_4_IGEOMETRYTYPESTRATEGY_H

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include "../../Canvas/ICanvas.h"

namespace shapes
{
    class IGeometryTypeStrategy
    {
    public:
        virtual void Draw(gfx::ICanvas& canvas, uint32_t color) const = 0;

        virtual void Move(double dx, double dy) = 0;

        [[nodiscard]] virtual std::string GetType() const = 0;

        [[nodiscard]] virtual std::string ToString() const = 0;

        virtual ~IGeometryTypeStrategy() = default;
    };
}
#endif //INC_4_IGEOMETRYTYPESTRATEGY_H
