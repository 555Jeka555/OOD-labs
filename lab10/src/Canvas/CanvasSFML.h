#ifndef LAB10_CANVASSFML_H
#define LAB10_CANVASSFML_H

#pragma once

#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CanvasSFML : public ICanvas
{
public:
    explicit CanvasSFML(sf::RenderTarget &target);

    void DrawLine(const Point &from, const Point &to) override;

    void DrawClosedPolyLine(const std::vector<Point> &) override;

    void DrawEllipse(RectD frame) override;

    void FillEllipse(RectD frame) override;

    void FillPolygon(const std::vector<Point> &) override;

    void SetFillColor(uint32_t) override;

    void SetLineColor(uint32_t) override;

    void SetLineThickness(unsigned int) override;

    void DrawText(const std::string &, const Point &position) override;

    void Capture(const std::string &outputFileName);

private:
    void DrawClosedPolyLineSegment(size_t index, const std::vector<Point> &points);

    sf::Color m_lineColor = sf::Color::White;
    sf::Color m_fillColor = sf::Color::Black;
    sf::Color m_backgroundColor;
    unsigned int m_lineThickness;
    sf::RenderTarget &m_renderTarget;
};


#endif //LAB10_CANVASSFML_H
