#ifndef LAB5_MODERNGRAPHICSADAPTER_H
#define LAB5_MODERNGRAPHICSADAPTER_H

#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace app
{
    class ModernGraphicsAdapter : public graphics_lib::ICanvas
    {
    public:
        explicit ModernGraphicsAdapter(modern_graphics_lib::ModernGraphicsRenderer& modernRenderer)
                : m_renderer(modernRenderer),
                  m_start(0, 0)
        {}

        void MoveTo(int x, int y) override
        {
            m_start = { x, y };
        }

        void LineTo(int x, int y) override
        {
            const modern_graphics_lib::Point end(x, y);

            m_renderer.DrawLine(m_start, end);

            m_start = end;
        }

    private:
        modern_graphics_lib::Point m_start;
        modern_graphics_lib::ModernGraphicsRenderer& m_renderer;
    };
}

#endif //LAB5_MODERNGRAPHICSADAPTER_H
