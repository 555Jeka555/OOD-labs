#ifndef LAB10_MENUVIEWPRESENTER_H
#define LAB10_MENUVIEWPRESENTER_H

#pragma once
#include "PictureDraftViewPresenter.h"
#include "../View/MenuView.h"

class MenuViewPresenter
{
public:
    MenuViewPresenter(MenuView& menuView, IPictureDraftViewPresenter& pictureDraftViewPresenter)
        :   m_menuView(menuView),
            m_pictureDraftViewPresenter(pictureDraftViewPresenter)
    {}

    void OnMouseDown(const Point& point, ICanvas& canvas)
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
        else if (width * 2/buttonCount <= point.m_x && point.m_x < width * 3/buttonCount)
        {
            m_pictureDraftViewPresenter.InsertShape(ShapeType::ELLIPSE);
        }
        else if (width * 3/buttonCount <= point.m_x && point.m_x < width * 4/buttonCount)
        {
            canvas.SaveToFile(NAME_SAVED_FILE);
        }
    }

private:
    constexpr static std::string NAME_SAVED_FILE = "foto.png";

    MenuView& m_menuView;
    IPictureDraftViewPresenter& m_pictureDraftViewPresenter;
};

#endif //LAB10_MENUVIEWPRESENTER_H
