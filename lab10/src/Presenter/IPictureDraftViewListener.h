#ifndef LAB10_IPICTUREDRAFTVIEWLISTENER_H
#define LAB10_IPICTUREDRAFTVIEWLISTENER_H

#pragma once
#include "../Common/Point.h"

class IPictureDraftViewListener
{
public:
    virtual void OnMouseDown(const Point&) = 0;

    virtual void OnDrag(const Point& offset, const Point& point) = 0;
    virtual void OnMouseUp(const Point&) = 0;

    virtual ~IPictureDraftViewListener() = default;
};

#endif //LAB10_IPICTUREDRAFTVIEWLISTENER_H
