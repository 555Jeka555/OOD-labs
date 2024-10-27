#ifndef LAB6_MODERNGRAPHICSCLASSADAPTER_H
#define LAB6_MODERNGRAPHICSCLASSADAPTER_H

#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace app {
    class ModernGraphicsClassAdapter
            : public graphics_lib::ICanvas, public modern_graphics_lib::ModernGraphicsRenderer {
    public:
        explicit ModernGraphicsClassAdapter(std::ostream &strm)
                : ModernGraphicsRenderer(strm),
                  m_start(0, 0) {}

        void MoveTo(int x, int y) override {
            m_start = {x, y};
        }

        void LineTo(int x, int y) override {
            modern_graphics_lib::Point end(x, y);

            DrawLine(m_start, end);

            m_start.x = end.x;
            m_start.y = end.y;
        }

    private:
        modern_graphics_lib::Point m_start;
    };
}

#endif //LAB6_MODERNGRAPHICSCLASSADAPTER_H
