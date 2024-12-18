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
        RectD rect0 = {100, 100, 100, 100};
        m_pictureDraft->InsertShape(
                std::make_shared<Shape>(
                        ShapeType::ELLIPSE,
                        rect0),
                        0
                );

        RectD rect1 = {100, 100, 100, 100};
        m_pictureDraft->InsertShape(
                std::make_shared<Shape>(
                        ShapeType::ELLIPSE,
                        rect1
                        ),
                1
        );

        RectD rect2 = {300, 300, 100, 100};
        m_pictureDraft->InsertShape(
                std::make_shared<Shape>(
                        ShapeType::TRIANGLE,
                        rect2),
                2
        );

        RectD rect3 = {400, 300, 100, 100};
        m_pictureDraft->InsertShape(
                std::make_shared<Shape>(
                        ShapeType::RECTANGLE,
                        rect3),
                3
        );

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
                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    auto mouseEventPressed = event->getIf<sf::Event::MouseButtonPressed>();
                    Point pointPressed = Point{(double)mouseEventPressed->position.x, (double)mouseEventPressed->position.y};
                    if (!isDragging)
                    {
                        clickPoint = pointPressed;
                    }
                    if (mouseEventPressed->button == sf::Mouse::Button::Left)
                    {
                        if (!(pictureDraftSize.m_y < pointPressed.m_y && pointPressed.m_y <= pictureDraftSize.m_y))
                        {
                            pictureDraftViewPresenter->OnMouseDown(pointPressed);
                        }
                    }
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clock.getElapsedTime().asMilliseconds() >= 10)
                {
                    isDragging = true;
                }
                else
                {
                    clock.restart();
                }
                if (event->is<sf::Event::MouseButtonReleased>())
                {
                    auto mouseEventReleased = event->getIf<sf::Event::MouseButtonReleased>();
                    Point pointReleased = { (double)mouseEventReleased->position.x, (double)mouseEventReleased->position.y };
                    pictureDraftViewPresenter->OnMouseUp(pointReleased);
                    isDragging = false;
                }
                if (isDragging && event->is<sf::Event::MouseLeft>())
                {
                    auto eventDraggingLeft = event->getIf<sf::Event::MouseButtonReleased>();
                    Point point = { (double)eventDraggingLeft->position.x, (double)eventDraggingLeft->position.y };
                    pictureDraftViewPresenter->OnMouseUp(point);
                    pictureDraftViewPresenter->OnMouseDown({ -1, -1 });
                }
                if (event->is<sf::Event::KeyPressed>())
                {
                    auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                    if (keyEvent->code == sf::Keyboard::Key::Delete)
                    {
                        pictureDraftViewPresenter->DeleteShape();
                    }

                    if (keyEvent->code == sf::Keyboard::Key::Z
                        && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)))
                    {
                        pictureDraftViewPresenter->Undo();
                    }

                    if (keyEvent->code == sf::Keyboard::Key::Y
                        && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)))
                    {
                        pictureDraftViewPresenter->Redo();
                    }
                }
            }
            if (isDragging) {
                auto point = sf::Mouse::getPosition(renderWindow);
                Point offset = {point.x - clickPoint.m_x, point.y - clickPoint.m_y};
                pictureDraftViewPresenter->OnDrag(offset, clickPoint);
                clickPoint.m_x += offset.m_x;
                clickPoint.m_y += offset.m_y;
            }


            renderWindow.clear(sf::Color::White);
            pictureDraftView.Draw(canvas);
            renderWindow.display();
        }
    }

    std::shared_ptr<PictureDraft> m_pictureDraft;
    std::shared_ptr<CommandHistory> m_commandHistory;
};


#endif //LAB10_APP_H
