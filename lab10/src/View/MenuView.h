#ifndef LAB10_MENUVIEW_H
#define LAB10_MENUVIEW_H

#pragma once

#include "../Canvas/ICanvas.h"

class MenuView
{
public:

    MenuView(double width, double height)
        :   m_width(width),
            m_height(height)
    {
        m_buttons = {
                "Triangle",
                "Rectangle",
                "Ellipse",
                "Save",
        };
    }

    void Show(ICanvas &canvas)
    {
        auto width = m_width / m_buttons.size();

        for (int i = 0; i < m_buttons.size(); i++)
        {
            ShowButton(
                    canvas,
                    {
                            width * i,
                            0,
                            width,
                            m_height
                    },
                    m_buttons[i]);
        }
    }

    [[nodiscard]] double GetWidth() const
    {
        return m_width;
    }

    [[nodiscard]] size_t GetCountButtons() const
    {
        return m_buttons.size();
    }

private:
    static constexpr RGBAColor DEFAULT_FILL_COLOR = 0x000000FF;
    static constexpr int DEFAULT_BUTTON_INDENT = 10;

    std::vector<std::string> m_buttons;
    double m_width;
    double m_height;

    static void ShowButton(ICanvas &canvas, const RectD &frame, const std::string &name)
    {
        Point leftTop = {frame.left, frame.top};
        Point rightBottom = {frame.left + frame.width, frame.top + frame.height};
        Point rightTop = {rightBottom.m_x, frame.top};
        Point leftBottom = {frame.left, rightBottom.m_y};

        canvas.SetFillColor(DEFAULT_FILL_COLOR);

        canvas.DrawLine({leftTop.m_x, leftTop.m_y}, {rightTop.m_x, rightTop.m_y});
        canvas.DrawLine(rightTop, rightBottom);
        canvas.DrawLine({rightBottom.m_x, rightBottom.m_y},
                        {leftBottom.m_x, leftBottom.m_y});
        canvas.DrawLine(leftBottom, leftTop);

        canvas.DrawText(name, {leftTop.m_x + DEFAULT_BUTTON_INDENT, leftTop.m_y + DEFAULT_BUTTON_INDENT});
    }
};

#endif //LAB10_MENUVIEW_H
