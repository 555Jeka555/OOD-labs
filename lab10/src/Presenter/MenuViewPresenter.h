#ifndef LAB10_MENUVIEWPRESENTER_H
#define LAB10_MENUVIEWPRESENTER_H

#pragma once
#include "PictureDraftViewPresenter.h"
#include "../View/MenuView.h"

class MenuViewPresenter
{
public:
    MenuViewPresenter(MenuView& menuView, PictureDraftViewPresenter& pictureDraftViewPresenter)
        :   m_menuView(menuView),
            m_pictureDraftViewPresenter(pictureDraftViewPresenter)
    {}

    void OnMouseDown(const Point& point)
    {
        auto width = m_menuView.GetWidth();
        auto buttonCount = (double)m_menuView.GetCountButtons();

        if (point.m_x < width / buttonCount)
        {
            m_pictureDraftViewPresenter.InsertShape(ShapeType::TRIANGLE);
        }
        else if (width / buttonCount <= point.m_x && point.m_x < width * 2/buttonCount)
        {
            m_pictureDraftViewPresenter.InsertShape(ShapeType::RECTANGLE);
        }
        else if (width * 2/buttonCount <= point.m_x && point.m_x < width)
        {
            m_pictureDraftViewPresenter.InsertShape(ShapeType::ELLIPSE);
        }
    }

private:
    MenuView& m_menuView;
    PictureDraftViewPresenter& m_pictureDraftViewPresenter;
};

#endif //LAB10_MENUVIEWPRESENTER_H
