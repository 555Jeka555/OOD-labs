#ifndef LAB10_DELETESHAPEUSECASE_H
#define LAB10_DELETESHAPEUSECASE_H

#pragma once
#include "../Model/ShapeSelection.h"
#include "../Model/PictureDraftApp.h"
#include "../History/ICommandStorage.h"
#include "../Command/GroupCommand.h"
#include "../Command/DeleteShapeCommand.h"

class DeleteShapeUseCase
{
public:
    DeleteShapeUseCase(
            PictureDraftApp& pictureDraft,
            ShapeSelection& selection,
            ICommandStorage& commandStorage)
        :   m_shapeSelection(selection),
            m_pictureDraft(pictureDraft),
            m_commandStorage(commandStorage)
    {}

    void Execute()
    {
        auto deleteShapesMacro = std::make_unique<GroupCommand>();
        auto domainPictureDraft = m_pictureDraft.GetPictureDraft();
        auto shapesToDelete = m_shapeSelection.GetSelectedShapes();
        for (auto&& shape : shapesToDelete)
        {
            deleteShapesMacro->AddCommand(std::make_unique<DeleteShapeCommand>(shape->GetShape(), domainPictureDraft, m_shapeSelection));
        }
        m_commandStorage.AddAndExecuteCommand(std::move(deleteShapesMacro));
    }

private:
    ShapeSelection& m_shapeSelection;
    PictureDraftApp& m_pictureDraft;
    ICommandStorage& m_commandStorage;
};

#endif //LAB10_DELETESHAPEUSECASE_H
