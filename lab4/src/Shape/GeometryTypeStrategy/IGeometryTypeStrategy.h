#ifndef INC_4_IGEOMETRYTYPESTRATEGY_H
#define INC_4_IGEOMETRYTYPESTRATEGY_H

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include "../../Canvas/ICanvas.h"
#include "../Color.h"

class IGeometryTypeStrategy
{
public:
    virtual void Draw(ICanvas& canvas, Color color) const = 0;

    virtual ~IGeometryTypeStrategy() = default;
};

#endif //INC_4_IGEOMETRYTYPESTRATEGY_H
