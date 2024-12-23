#ifndef LAB10_SHAPEVIEWPRESENTER_H
#define LAB10_SHAPEVIEWPRESENTER_H

#pragma once
#include "../App/Model/ShapeAppModel.h"
#include "../App/Model/ShapeSelection.h"
#include "../App/UseCase/IUseCaseFactory.h"
#include "../View/ShapeView.h"

class ShapeViewPresenter
{
public:

    ShapeViewPresenter(
            const std::shared_ptr<ShapeAppModel>& model,
            IUseCaseFactory& useCaseFactory,
            IShapeSelection& selectionModel,
            const std::shared_ptr<ShapeView>& shapeView)
        :   m_shapeApp(model),
            m_shapeSelection(selectionModel),
            m_shapeView(shapeView),
            m_useCaseFactory(useCaseFactory)
    {
        m_shapeApp->DoOnFrameChanged([=, *this](const RectD& frame) {
            m_shapeView->SetFrame(frame);
        });
    }

    [[nodiscard]] std::shared_ptr<ShapeView> GetShapeView() const
    {
        return m_shapeView;
    }

    void OnMouseDown(const Point& point)
    {
        bool isPointBelongShape = false;
        auto frame = m_shapeView->GetFrame();
        switch (m_shapeView->GetShapeType())
        {
            case ShapeType::RECTANGLE:
                isPointBelongShape = true;
                break;
            case ShapeType::TRIANGLE:
            {
                Point vertex1 = { frame.left, frame.top + frame.height };
                Point vertex2 = { frame.left + frame.width / 2, frame.top };
                Point vertex3 = { frame.left + frame.width, frame.top + frame.height };

                auto sign1 = std::copysign(1, (vertex1.m_x - point.m_x) * (vertex2.m_y - vertex1.m_y) - (vertex2.m_x - vertex1.m_x) * (vertex1.m_y - point.m_y));
                auto sign2 = std::copysign(1, (vertex2.m_x - point.m_x) * (vertex3.m_y - vertex2.m_y) - (vertex3.m_x - vertex2.m_x) * (vertex2.m_y - point.m_y));
                auto sign3 = std::copysign(1, (vertex3.m_x - point.m_x) * (vertex1.m_y - vertex3.m_y) - (vertex1.m_x - vertex3.m_x) * (vertex3.m_y - point.m_y));

                isPointBelongShape = (sign1 == sign2) && (sign2 == sign3);
            }
                break;
            case ShapeType::ELLIPSE:
            {
                Point center = { frame.left + frame.width / 2,
                                 frame.top + frame.height / 2 };
                isPointBelongShape = (pow(point.m_x - center.m_x, 2) / pow(frame.width / 2, 2) +
                                      pow(point.m_y - center.m_y, 2) / pow(frame.height / 2, 2)) <= 1;
            }
                break;
            default:
                break;
        }

        auto selectedShapes = m_shapeSelection.GetSelectedShapes();
        bool isShapeSelected = std::find_if(selectedShapes.begin(), selectedShapes.end(), [&, this](const std::shared_ptr<ShapeAppModel>& shape) {
            return shape->GetId() == m_shapeApp->GetId();
        }) != selectedShapes.end();

        if (isPointBelongShape && !isShapeSelected)
        {
            m_shapeSelection.SetSelectedShapes({ m_shapeApp });
        }
    }

    void OnDrag(const Point& offset, const Point& point)
    {
        auto frame = m_shapeApp->GetFrame();
        auto useCase = m_useCaseFactory.CreateResizeShapeUseCase();
        if (IsOnCorner({ frame.left, frame.top }, point))
        {
            useCase->Resize(offset, DirectionPoint::RIGHT_BOTTOM);
        }
        else if (IsOnCorner({ frame.left + frame.width - DEFAULT_SELECTION_CORNER_SIZE, frame.top }, point))
        {
            useCase->Resize(offset, DirectionPoint::LEFT_BOTTOM);
        }
        else if (IsOnCorner({ frame.left + frame.width - DEFAULT_SELECTION_CORNER_SIZE, frame.top + frame.height - DEFAULT_SELECTION_CORNER_SIZE }, point))
        {
            useCase->Resize(offset, DirectionPoint::LEFT_TOP);
        }
        else if (IsOnCorner({ frame.left, frame.top + frame.height - DEFAULT_SELECTION_CORNER_SIZE }, point))
        {
            useCase->Resize(offset, DirectionPoint::RIGHT_TOP);
        }
        else
        {
            auto useCase = m_useCaseFactory.CreateMoveShapeUseCase();
            useCase->Move(offset);
        }

        auto selectedShapes = m_shapeSelection.GetSelectedShapes();
        for (auto&& shape : selectedShapes)
        {
            CorectFrameBorders(shape);
        }
    }

    void OnMouseUp(const Point& point)
    {
        auto frame = m_shapeApp->GetFrame();
        if (IsOnCorner({ frame.left, frame.top }, point) ||
            IsOnCorner({ frame.left + frame.width - DEFAULT_SELECTION_CORNER_SIZE, frame.top }, point) ||
            IsOnCorner({ frame.left + frame.width - DEFAULT_SELECTION_CORNER_SIZE, frame.top + frame.height - DEFAULT_SELECTION_CORNER_SIZE }, point) ||
            IsOnCorner({ frame.left, frame.top + frame.height - DEFAULT_SELECTION_CORNER_SIZE }, point))
        {
            auto useCase = m_useCaseFactory.CreateResizeShapeUseCase();
            useCase->Execute();
        }
        else
        {
            auto useCase = m_useCaseFactory.CreateMoveShapeUseCase();
            useCase->Execute();
        }
    }

    void SetCorrectFrameBorders(size_t width, size_t height)
    {
        m_respectFrameWidth = width;
        m_respectFrameHeight = height;
    }

    [[nodiscard]] size_t GetRespectFrameWidth() const
    {
        return m_respectFrameWidth;
    }

    [[nodiscard]] size_t GetRespectFrameHeight() const
    {
        return m_respectFrameHeight;
    }

private:
    constexpr static double DEFAULT_SELECTION_CORNER_SIZE = 10;
    
    std::shared_ptr<ShapeAppModel> m_shapeApp;
    IUseCaseFactory& m_useCaseFactory;
    IShapeSelection& m_shapeSelection;
    std::shared_ptr<ShapeView> m_shapeView;
    size_t m_respectFrameWidth = SIZE_MAX;
    size_t m_respectFrameHeight = SIZE_MAX;
    
    static bool IsOnCorner(const Point& leftTop, const Point& point)
    {
        return (leftTop.m_x <= point.m_x && point.m_x <= leftTop.m_x + DEFAULT_SELECTION_CORNER_SIZE &&
                leftTop.m_y <= point.m_y && point.m_y <= leftTop.m_y + DEFAULT_SELECTION_CORNER_SIZE);
    }

    void CorectFrameBorders(const std::shared_ptr<ShapeAppModel>& shape) const
    {
        bool frameChanged = false;
        auto frame = shape->GetFrame();
        if (frame.left < 0)
        {
            frameChanged = true;
            frame.left = 0;
        }
        if (frame.top < 0)
        {
            frameChanged = true;
            frame.top = 0;
        }
        if (m_respectFrameWidth < frame.width)
        {
            frameChanged = true;
            frame.width = m_respectFrameWidth;
        }
        if (m_respectFrameHeight < frame.height)
        {
            frameChanged = true;
            frame.height = m_respectFrameHeight;
        }
        if (m_respectFrameWidth - frame.width < frame.left)
        {
            frameChanged = true;
            frame.left = m_respectFrameWidth - frame.width;
        }
        if (m_respectFrameHeight - frame.height < frame.top)
        {
            frameChanged = true;
            frame.top = m_respectFrameHeight - frame.height;
        }
        if (frameChanged)
        {
            shape->SetFrame(frame);
        }
    }
};

#endif //LAB10_SHAPEVIEWPRESENTER_H
