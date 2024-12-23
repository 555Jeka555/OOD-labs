#ifndef LAB10_RESIZESHAPEUSECASE_H
#define LAB10_RESIZESHAPEUSECASE_H

#pragma once
#include "../Model/ShapeSelection.h"
#include "../Model/PictureDraftAppModel.h"
#include "../History/ICommandStorage.h"
#include "../Command/GroupCommand.h"
#include "../Command/ChangeRectShapeCommand.h"
#include "../../Common/Point.h"
#include "IResizeShapeUseCase.h"

class ResizeShapeUseCase : public IResizeShapeUseCase
{
public:

    ResizeShapeUseCase(IShapeSelection& selection, ICommandStorage& commandStorage)
        :   m_shapeSelection(selection),
            m_commandStorage(commandStorage)
    {
    }

    void Resize(const Point& offset, DirectionPoint directionPoint) override
    {
        auto shapesToResize = m_shapeSelection.GetSelectedShapes();
        for (auto&& shape : shapesToResize)
        {
            ResizeShape(shape, offset, directionPoint);
        }
    }

    void Execute() override
    {
        auto resizeShapesGroupCommand = std::make_unique<GroupCommand>();
        auto shapesToResize = m_shapeSelection.GetSelectedShapes();
        for (auto&& shape : shapesToResize)
        {
            resizeShapesGroupCommand->AddCommand(std::make_unique<ChangeRectShapeCommand>(shape, m_shapeSelection));
        }
        m_commandStorage.AddAndExecuteCommand(std::move(resizeShapesGroupCommand));
    }

private:
    constexpr static double MIN_WIDTH = 30;
    constexpr static double MIN_HEIGHT = 30;

    IShapeSelection& m_shapeSelection;
    ICommandStorage& m_commandStorage;

    void ResizeShape(const std::shared_ptr<ShapeAppModel>& shape, const Point& offset, DirectionPoint directionPoint) {
        auto frame = shape->GetFrame();
        double newWidth;
        double newHeight;

        switch (directionPoint)
        {
            case DirectionPoint::LEFT_TOP:
                newWidth = frame.width + offset.m_x;
                frame.width = std::max(MIN_WIDTH, newWidth);

                newHeight = frame.height + offset.m_y;
                frame.height = std::max(MIN_HEIGHT, newHeight);

                shape->SetFrame(frame);
                return;
            case DirectionPoint::RIGHT_TOP:
                newWidth = frame.width - offset.m_x;
                frame.width = std::max(MIN_WIDTH, newWidth);

                newHeight = frame.height + offset.m_y;
                frame.height = std::max(MIN_HEIGHT, newHeight);

                frame.left += offset.m_x;
                shape->SetFrame(frame);
                return;
            case DirectionPoint::RIGHT_BOTTOM:
                newWidth = frame.width - offset.m_x;
                frame.width = std::max(MIN_WIDTH, newWidth);

                newHeight = frame.height - offset.m_y;
                frame.height = std::max(MIN_HEIGHT, newHeight);

                frame.left += offset.m_x;
                frame.top += offset.m_y;
                shape->SetFrame(frame);
                return;
            case DirectionPoint::LEFT_BOTTOM:
                newWidth = frame.width + offset.m_x;
                frame.width = std::max(MIN_WIDTH, newWidth);

                newHeight = frame.height - offset.m_y;
                frame.height = std::max(MIN_HEIGHT, newHeight);

                frame.top += offset.m_y;
                shape->SetFrame(frame);
                return;
            default:
                throw std::invalid_argument("Unknown base point type was given");
        }
    }
};


#endif //LAB10_RESIZESHAPEUSECASE_H