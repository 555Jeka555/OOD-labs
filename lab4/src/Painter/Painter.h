#ifndef LAB4_PAINTER_H
#define LAB4_PAINTER_H

#include "IPainter.h"

class Painter : public IPainter
{
public:
    void DrawPicture(const PictureDraft& draft, gfx::ICanvas& canvas) override
    {
        for (const auto& shape : draft) {
            shape->Draw(canvas);
        }
    }
};

#endif //LAB4_PAINTER_H
