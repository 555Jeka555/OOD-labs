#ifndef LAB10_APP_H
#define LAB10_APP_H

#pragma once

#include <iostream>
#include <optional>
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
    constexpr static int WIDTH_SIZE = 800; 
    constexpr static int HEIGHT_SIZE = 600;
    
    std::shared_ptr<PictureDraft> m_pictureDraft;
    std::shared_ptr<CommandHistory> m_commandHistory;
    
    
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

        PictureDraftView pictureDraftView(pictureDraftApp, shapeSelection, WIDTH_SIZE, HEIGHT_SIZE);
        auto pictureDraftViewPresenter = std::make_shared<PictureDraftViewPresenter>(
                shapeSelection,
                pictureDraftView,
                pictureDraftApp,
                useCaseFactory,
                shapeViewStrategyFactory
        );
        
        sf::ContextSettings settings;
        settings.antiAliasingLevel = 8;
        auto renderWindow = sf::RenderWindow(
                sf::VideoMode({WIDTH_SIZE,HEIGHT_SIZE}),
                "App",
                sf::Style::Default, sf::State::Windowed, settings);
        auto canvas = CanvasSFML(renderWindow);
        
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

                CheckMouseButtonPressed(event, pictureDraftViewPresenter, isDragging, clickPoint);
                CheckIsDragging(clock, isDragging);
                CheckMouseButtonReleased(event, pictureDraftViewPresenter, isDragging);
                CheckMouseLeft(event, pictureDraftViewPresenter, isDragging);
                CheckKeys(event, pictureDraftViewPresenter);
            }
            DragShape(renderWindow, pictureDraftViewPresenter, isDragging, clickPoint);

            renderWindow.clear(sf::Color::White);
            pictureDraftView.Draw(canvas);
            renderWindow.display();
        }
    }

    static void CheckMouseButtonPressed(
        const std::optional<sf::Event> & event,
        const std::shared_ptr<PictureDraftViewPresenter>& pictureDraftViewPresenter,
        bool& isDragging,
        Point& clickPoint
    )
    {
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
                if (!(HEIGHT_SIZE < pointPressed.m_y && pointPressed.m_y <= HEIGHT_SIZE))
                {
                    pictureDraftViewPresenter->OnMouseDown(pointPressed);
                }
            }
        }
    }

    static void CheckIsDragging(
        sf::Clock& clock,
        bool& isDragging
    )
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clock.getElapsedTime().asMilliseconds() >= 10)
        {
            isDragging = true;
        }
        else
        {
            clock.restart();
        }
    }

    static void CheckMouseButtonReleased(
        const std::optional<sf::Event> & event,
        const std::shared_ptr<PictureDraftViewPresenter>& pictureDraftViewPresenter,
        bool& isDragging
    )
    {
        if (event->is<sf::Event::MouseButtonReleased>())
        {
            auto mouseEventReleased = event->getIf<sf::Event::MouseButtonReleased>();
            Point pointReleased = { (double)mouseEventReleased->position.x, (double)mouseEventReleased->position.y };
            pictureDraftViewPresenter->OnMouseUp(pointReleased);
            isDragging = false;
        }
    }

    static void CheckMouseLeft(
        const std::optional<sf::Event> & event,
        const std::shared_ptr<PictureDraftViewPresenter>& pictureDraftViewPresenter,
        const bool& isDragging
    )
    {
        if (isDragging && event->is<sf::Event::MouseLeft>())
        {
            auto eventDraggingLeft = event->getIf<sf::Event::MouseButtonReleased>();
            Point point = { (double)eventDraggingLeft->position.x, (double)eventDraggingLeft->position.y };
            pictureDraftViewPresenter->OnMouseUp(point);
            pictureDraftViewPresenter->OnMouseDown({ -1, -1 });
        }
    }

    static void CheckKeys(
        const std::optional<sf::Event> & event,
        const std::shared_ptr<PictureDraftViewPresenter>& pictureDraftViewPresenter
    )
    {
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

    static void DragShape(
        const sf::RenderWindow & renderWindow,
        const std::shared_ptr<PictureDraftViewPresenter>& pictureDraftViewPresenter,
        const bool& isDragging,
        Point& clickPoint
    )
    {
        if (isDragging) {
            auto point = sf::Mouse::getPosition(renderWindow);
            Point offset = {point.x - clickPoint.m_x, point.y - clickPoint.m_y};
            pictureDraftViewPresenter->OnDrag(offset, clickPoint);
            clickPoint.m_x += offset.m_x;
            clickPoint.m_y += offset.m_y;
        }
    }
};


#endif //LAB10_APP_H
