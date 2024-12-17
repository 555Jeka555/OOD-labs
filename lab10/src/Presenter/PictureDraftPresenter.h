#ifndef LAB10_PICTUREDRAFTPRESENTER_H
#define LAB10_PICTUREDRAFTPRESENTER_H

#pragma once
#include "IPictureDraftViewListener.h"
#include "../App/Model/ShapeSelection.h"
#include "../View/PictureDraftView.h"
#include "../Presenter/ShapeViewPresenter.h"
#include "../App/UseCase/IUseCaseFactory.h"
#include "../View/IShapeViewStrategyFactory.h"

class PictureDraftViewPresenter : public IPictureDraftViewListener
{
public:
    PictureDraftViewPresenter(
            ShapeSelection& selectionModel,
            PictureDraftView& pictureDraftView,
            PictureDraftApp& pictureDraftApp,
            IUseCaseFactory& useCaseFactory,
            IShapeViewStrategyFactory& shapeViewStrategyFactory)
            : m_shapeSelectionModel(selectionModel)
            , m_pictureDraftView(pictureDraftView)
            , m_pictureDraftApp(pictureDraftApp)
            , m_useCaseFactory(useCaseFactory)
            , m_shapeViewStrategyFactory(shapeViewStrategyFactory)
    {
        auto shapeSize = m_pictureDraftApp.GetShapeCount();
        for (size_t i = 0; i < shapeSize; ++i)
        {
            CreateShapeView(i);
        }

        m_pictureDraftApp.DoOnShapeAdded([this](size_t index) {
            CreateShapeView(index);
            m_shapeSelectionModel.SetSelectedShapes({ m_pictureDraftApp.GetShape(index) });
        });

        m_pictureDraftApp.DoOnShapeDeleted([this](size_t index, std::shared_ptr<ShapeApp> shape) {
            CleanUpShapeView(index, shape);
            m_shapeSelectionModel.SetSelectedShapes({});
        });
    }

    void OnMouseDown(const Point& point) override
    {
        auto shapesSize = m_pictureDraftApp.GetShapeCount();
        if (shapesSize == 0)
        {
            return;
        }
        auto IsShapeMouseDown = false;
        for (int i = shapesSize - 1; i >= 0; --i)
        {
            auto shape = m_pictureDraftApp.GetShape(i);
            auto frame = shape->GetFrame();
            if (frame.left <= point.m_x && point.m_x <= frame.left + frame.width &&
                frame.top <= point.m_y && point.m_y <= frame.top + frame.height)
            {
                for (auto&& shapeViewPresenter : m_shapeViewPresenters)
                {
                    if (shapeViewPresenter->GetShapeView()->GetId() == shape->GetId())
                    {
                        shapeViewPresenter->OnMouseDown(point);
                        auto selectedShapes = m_shapeSelectionModel.GetSelectedShapes();
                        if (selectedShapes.size() != 0 &&
                            selectedShapes.back()->GetId() == shape->GetId() )
                        {
                            IsShapeMouseDown = true;
                            break;
                        }
                    }
                }
                if (IsShapeMouseDown)
                {
                    break;
                }
            }
        }
        if (!IsShapeMouseDown)
        {
            m_shapeSelectionModel.SetSelectedShapes({});
        }
    }

    void OnDrag(const Point& offset, const Point& point) override
    {
        auto shapesSize = m_pictureDraftApp.GetShapeCount();
        if (shapesSize == 0)
        {
            return;
        }
        auto selectedShapes = m_shapeSelectionModel.GetSelectedShapes();
        for (int i = shapesSize - 1; i >= 0; --i)
        {
            auto shape = m_pictureDraftApp.GetShape(i);
            auto frame = shape->GetFrame();
            if (frame.left <= point.m_x && point.m_x <= frame.left + frame.width &&
                frame.top <= point.m_y && point.m_y <= frame.top + frame.height)
            {
                for (auto&& shapeViewPresenter : m_shapeViewPresenters)
                {
                    if (shapeViewPresenter->GetShapeView()->GetId() == shape->GetId() &&
                        std::find_if(selectedShapes.begin(), selectedShapes.end(), [&, shape](const std::shared_ptr<ShapeApp>& currShape) {
                            return currShape->GetId() == shape->GetId();
                        }) != selectedShapes.end())
                    {
                        shapeViewPresenter->OnDrag(offset, point);
                        break;
                    }
                }
            }
        }
    }

    void OnMouseUp(const Point& point) override
    {
        auto shapesSize = m_pictureDraftApp.GetShapeCount();
        if (shapesSize == 0)
        {
            return;
        }
        for (int i = shapesSize - 1; i >= 0; --i)
        {
            auto shape = m_pictureDraftApp.GetShape(i);
            auto frame = shape->GetFrame();
            if (frame.left <= point.m_x && point.m_x <= frame.left + frame.width && frame.top <= point.m_y && point.m_y <= frame.top + frame.height)
            {
                for (auto&& shapeViewPresenter : m_shapeViewPresenters)
                {
                    if (shapeViewPresenter->GetShapeView()->GetId() == shape->GetId())
                    {
                        shapeViewPresenter->OnMouseUp(point);
                        break;
                    }
                }
                break;
            }
        }
    }

    void InsertShape(ShapeType type)
    {
        auto useCase = m_useCaseFactory.CreateInsertShapeUseCase(m_pictureDraftApp);
        auto index = m_pictureDraftApp.GetShapeCount();
        useCase->Execute(index, type);
    }

    void DeleteShape()
    {
        auto useCase = m_useCaseFactory.CreateDeleteShapeUseCase(m_pictureDraftApp);
        useCase->Execute();
    }

    void Undo()
    {
        m_pictureDraftApp.Undo();
    }

    void Redo()
    {
        m_pictureDraftApp.Redo();
    }

private:
    void CreateShapeView(size_t index)
    {
        auto shapeApp = m_pictureDraftApp.GetShape(index);
        auto shapeView = std::make_shared<ShapeView>(
                shapeApp->GetId(),
                m_shapeViewStrategyFactory.Create(shapeApp->GetType()),
                shapeApp->GetFrame(),
                shapeApp->GetType(),
                shapeApp->GetFillColor()->GetColor(),
                shapeApp->GetLineColor()->GetColor(),
                shapeApp->GetLineColor()->GetThickness()
         );
        auto shapeViewPresenter = std::make_shared<ShapeViewPresenter>(shapeApp, m_useCaseFactory, m_shapeSelectionModel, shapeView);
        shapeViewPresenter->SetRespectFrameBorders(m_pictureDraftView.GetWidth(), m_pictureDraftView.GetHeight());
        m_shapeViewPresenters.push_back(shapeViewPresenter);
        m_pictureDraftView.InsertShapeView(index, std::move(shapeView));
    }

    void CleanUpShapeView(size_t index, const std::shared_ptr<ShapeApp>& shape)
    {
        auto id = shape->GetId();
        m_shapeViewPresenters.erase(std::find_if(m_shapeViewPresenters.begin(), m_shapeViewPresenters.end(),
                                                 [&id](const std::shared_ptr<ShapeViewPresenter>& presenter) {
                                                     return presenter->GetShapeView()->GetId() == id;
                                                 }));
        m_pictureDraftView.DeleteShapeView(index);
    }

    ShapeSelection& m_shapeSelectionModel;
    PictureDraftView& m_pictureDraftView;
    PictureDraftApp& m_pictureDraftApp;
    std::vector<std::shared_ptr<ShapeViewPresenter>> m_shapeViewPresenters;
    IUseCaseFactory& m_useCaseFactory;
    IShapeViewStrategyFactory& m_shapeViewStrategyFactory;
};

#endif //LAB10_PICTUREDRAFTPRESENTER_H
