#ifndef LAB4_CLIENT_H
#define LAB4_CLIENT_H

#include "Canvas/ICanvas.h"
#include "Painter/IPainter.h"
#include "Designer/IDesigner.h"

class Client
{
public:
    explicit Client(IDesigner & designer)
        : m_designer(designer)
    {}

    void HandleCommand(std::istream & inputData, gfx::ICanvas & canvas, IPainter & painter)
    {
        PictureDraft pictureDraft = m_designer.CreateDraft(inputData);

        painter.DrawPicture(pictureDraft, canvas);
    }

private:
    IDesigner & m_designer;
};

#endif //LAB4_CLIENT_H
