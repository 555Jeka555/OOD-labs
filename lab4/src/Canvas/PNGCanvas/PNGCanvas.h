////#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
////#endif // STB_IMAGE_WRITE_IMPLEMENTATION
////#ifndef STB_TRUETYPE_IMPLEMENTATION
//#define STB_TRUETYPE_IMPLEMENTATION
//#include "stb_truetype.h"
////#endif // STB_TRUETYPE_IMPLEMENTATION

// TODO Защитить заголовочные файлы от повторного включения
#pragma once

#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include "../ICanvas.h"

#ifndef PNG_CANVAS_H
#define PNG_CANVAS_H

namespace gfx
{
    struct Color {
        uint8_t r, g, b, a;
    };

    Color StringToColor(uint32_t color);

    class PNGCanvas : public ICanvas
    {
    public:
        PNGCanvas(int w, int h) : width(w), height(h), currentColor({255, 255, 255, 255})
        {
            pixels.resize(width * height * 4, 255);
        }

        // TODO Убрать из деструктора

        void SetColor(uint32_t color) override
        {
            currentColor = StringToColor(color);
        }

        void DrawLine(double fromX, double fromY, double toX, double toY) override
        {
            int ix1 = static_cast<int>(std::round(fromX));
            int iy1 = static_cast<int>(std::round(fromY));
            int ix2 = static_cast<int>(std::round(toX));
            int iy2 = static_cast<int>(std::round(toY));

            int dx = std::abs(ix2 - ix1), dy = std::abs(iy2 - iy1);
            int sx = (ix1 < ix2) ? 1 : -1;
            int sy = (iy1 < iy2) ? 1 : -1;
            int err = dx - dy;

            while (true)
            {
                PutPixel(ix1, iy1);
                if (ix1 == ix2 && iy1 == iy2) break;
                int e2 = 2 * err;
                if (e2 > -dy)
                {
                    err -= dy; ix1 += sx;
                }
                if (e2 < dx) { err += dx; iy1 += sy; }
            }
        }

        void DrawEllipse(double cx, double cy, double rx, double ry) override
        {
            int segments = 100;
            double angleStep = 2 * M_PI / segments;

            double prevX = cx + rx;
            double prevY = cy;

            for (int i = 1; i <= segments; ++i)
            {
                double angle = i * angleStep;
                double newX = cx + rx * cos(angle);
                double newY = cy + ry * sin(angle);
                DrawLine(prevX, prevY, newX, newY);
                prevX = newX;
                prevY = newY;
            }
        }

        void SaveToFile(const std::string& filename);

    private:
        int width, height;
        Color currentColor{};
        std::vector<uint8_t> pixels;

        void PutPixel(int x, int y)
        {
            if (x >= 0 && x < width && y >= 0 && y < height)
            {
                int index = 4 * (y * width + x);
                pixels[index] = currentColor.r;
                pixels[index + 1] = currentColor.g;
                pixels[index + 2] = currentColor.b;
                pixels[index + 3] = currentColor.a;
            }
        }
    };
}

#endif // PNG_CANVAS_H
