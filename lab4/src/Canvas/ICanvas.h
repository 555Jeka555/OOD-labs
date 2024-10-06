#ifndef INC_1_1_ICANVAS_H
#define INC_1_1_ICANVAS_H

#include <string>
#include <cstdint>

namespace gfx
{
    class ICanvas
    {
    public:

        virtual void SetColor(uint32_t color) = 0;

        virtual void DrawLine(double fromX, double fromY, double toX, double toY) = 0;

        virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;

        virtual ~ICanvas() = default;
    };
}

#endif //INC_1_1_ICANVAS_H