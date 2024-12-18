#ifndef LAB10_MOVESHAPEUSECASE_H
#define LAB10_MOVESHAPEUSECASE_H

#pragma once
#include "../Model/ShapeSelection.h"
#include "../Model/PictureDraftApp.h"
#include "../History/ICommandStorage.h"
#include "../Command/GroupCommand.h"
#include "../Command/ChangeRectShapeCommand.h"
#include "../../Common/Point.h"

class MoveShapeUseCase
{
public:
    MoveShapeUseCase(ShapeSelection& selection, ICommandStorage& commandStorage)
            :   m_shapeSelection(selection),
                m_commandStorage(commandStorage)
    {
    }

    void Move(const Point& offset)
    {
        auto shapesToMove = m_shapeSelection.GetSelectedShapes();
        for (auto&& shape : shapesToMove)
        {
            auto frame = shape->GetFrame();
            frame.left += offset.m_x;
            frame.top += offset.m_y;
            if (offset.m_x != 0 || offset.m_y != 0)
            {
                shape->SetFrame(frame);
            }
        }
    }

    void Execute()
    {
        auto moveShapesGroupCommand = std::make_unique<GroupCommand>();
        auto shapesToMove = m_shapeSelection.GetSelectedShapes();
        for (auto&& shape : shapesToMove)
        {
            moveShapesGroupCommand->AddCommand(std::make_unique<ChangeRectShapeCommand>(shape, m_shapeSelection));
        }
        m_commandStorage.AddAndExecuteCommand(std::move(moveShapesGroupCommand));
    }

private:
    ShapeSelection& m_shapeSelection;
    ICommandStorage& m_commandStorage;
};

#endif //LAB10_MOVESHAPEUSECASE_H
