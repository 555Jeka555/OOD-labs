#ifndef LAB4_IPAINTER_H
#define LAB4_IPAINTER_H

#include "../Designer/PictureDraft.h"
#include "../Canvas/ICanvas.h"

class IPainter
{
public:
    virtual void DrawPicture(const PictureDraft& draft, ICanvas& canvas) = 0;
};

#endif //LAB4_IPAINTER_H
