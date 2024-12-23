#ifndef LAB10_IPICTUREDRAFTVIEWPRESENTER_H
#define LAB10_IPICTUREDRAFTVIEWPRESENTER_H

#pragma once
#include "../Common/Point.h"
#include "../Common/ShapeType.h"

class IPictureDraftViewPresenter
{
public:
    virtual void OnMouseDown(const Point& point) = 0;

    virtual void OnDrag(const Point& offset, const Point& point) = 0;

    virtual void OnMouseUp(const Point& point) = 0;

    virtual void InsertShape(ShapeType type) = 0;

    virtual void DeleteShape() = 0;

    virtual void Undo() = 0;

    virtual void Redo() = 0;

    ~IPictureDraftViewPresenter() = default;
};

#endif //LAB10_IPICTUREDRAFTVIEWPRESENTER_H
