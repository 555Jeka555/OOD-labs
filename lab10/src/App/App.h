#ifndef LAB10_APP_H
#define LAB10_APP_H

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Canvas/CanvasSFML.h"
#include "History/CommandHistory.h"
#include "Model/PictureDraftApp.h"
#include "Model/ShapeSelection.h"
#include "../Model/PictureDraft.h"
#include "../Model/Shape.h"
#include "../Common/Point.h"
#include "../Presenter/PictureDraftPresenter.h"
#include "UseCase/UseCaseFactory.h"
#include "../View/ShapeViewStrategyFactory.h"

class App
{
public:

    App()
    {
        m_pictureDraft = std::make_shared<PictureDraft>();
        m_commandHistory = std::make_shared<CommandHistory>();
    }

    void Run()
    {
        InitEditWindow();
    }

private:
    void InitEditWindow() {
        PictureDraftApp pictureDraftApp(m_pictureDraft, m_commandHistory);
        ShapeSelection shapeSelection;
        auto useCaseFactory = UseCaseFactory(shapeSelection, *m_commandHistory);
        auto shapeViewStrategyFactory = ShapeViewStrategyFactory();

        sf::ContextSettings settings;
        settings.antiAliasingLevel = 8;
        Point pictureDraftSize = {800, 600};
        auto renderWindow = sf::RenderWindow(
                sf::VideoMode(
                        {
                                (unsigned int) pictureDraftSize.m_x,
                                (unsigned int) (pictureDraftSize.m_y)}
                ),
                "App",
                sf::Style::Default, sf::State::Windowed, settings);
        auto canvas = CanvasSFML(renderWindow);

        PictureDraftView pictureDraftView(pictureDraftApp, shapeSelection, pictureDraftSize.m_x, pictureDraftSize.m_y);
        auto pictureDraftViewPresenter = std::make_shared<PictureDraftViewPresenter>(
                shapeSelection,
                pictureDraftView,
                pictureDraftApp,
                useCaseFactory,
                shapeViewStrategyFactory
        );

        bool isDragging = false;
        Point clickPoint;
        sf::Clock clock;
        while (renderWindow.isOpen())
        {
            while (true)
            {
                auto event = renderWindow.pollEvent();
                if (!event.has_value())
                {
                    break;
                }

                if (event->is<sf::Event::Closed>())
                {
                    renderWindow.close();
                    break;
                }
                if (event->is<sf::Event::MouseButtonReleased>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();

                    Point point = {(double) mouseEvent->position.x, (double) mouseEvent->position.y};
                    if (!isDragging) {
                        clickPoint = point;
                    }
                    if (mouseEvent->button == sf::Mouse::Button::Left) {
                        pictureDraftViewPresenter->OnMouseDown(point);
                    }
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clock.getElapsedTime().asMilliseconds() >= 100) {
                    isDragging = true;
                } else {
                    clock.restart();
                }
            }
            if (isDragging) {
                auto point = sf::Mouse::getPosition(renderWindow);
                Point offset = {point.x - clickPoint.m_x, point.y - clickPoint.m_y};
                pictureDraftViewPresenter->OnDrag(offset, clickPoint);
                clickPoint.m_x += offset.m_x;
                clickPoint.m_y += offset.m_y;
            }

            // clear the window with black color
            renderWindow.clear(sf::Color::White);

            // window.draw(...);
            pictureDraftView.Show(canvas);

            // end the current frame
            renderWindow.display();
        }
    }

    std::shared_ptr<PictureDraft> m_pictureDraft;
    std::shared_ptr<CommandHistory> m_commandHistory;
};


#endif //LAB10_APP_H
