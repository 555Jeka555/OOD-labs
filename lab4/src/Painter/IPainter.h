#ifndef LAB4_IPAINTER_H
#define LAB4_IPAINTER_H

#include "../PictureDraft/PictureDraft.h"
#include "../Canvas/ICanvas.h"

class IPainter
{
public:
    virtual void DrawPicture(const PictureDraft& draft, gfx::ICanvas& canvas) = 0;

    virtual ~IPainter() = default;
};

#endif //LAB4_IPAINTER_H
