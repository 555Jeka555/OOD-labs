#ifndef LAB10_DELETESHAPEUSECASE_H
#define LAB10_DELETESHAPEUSECASE_H

#pragma once
#include "../Model/ShapeSelection.h"
#include "../Model/PictureDraftAppModel.h"
#include "../History/ICommandStorage.h"
#include "../Command/GroupCommand.h"
#include "../Command/DeleteShapeCommand.h"
#include "IDeleteShapeUseCase.h"

class DeleteShapeUseCase : public IDeleteShapeUseCase
{
public:
    DeleteShapeUseCase(
            PictureDraftAppModel& pictureDraft,
            IShapeSelection& selection,
            ICommandStorage& commandStorage)
        :   m_shapeSelection(selection),
            m_pictureDraft(pictureDraft),
            m_commandStorage(commandStorage)
    {}

    void Execute() override
    {
        auto deleteShapesGroupCommand = std::make_unique<GroupCommand>();
        auto domainPictureDraft = m_pictureDraft.GetPictureDraft();
        auto shapesToDelete = m_shapeSelection.GetSelectedShapes();
        for (auto&& shape : shapesToDelete)
        {
            deleteShapesGroupCommand->AddCommand(std::make_unique<DeleteShapeCommand>(shape->GetShape(), domainPictureDraft, m_shapeSelection));
        }
        m_commandStorage.AddAndExecuteCommand(std::move(deleteShapesGroupCommand));
    }

private:
    IShapeSelection& m_shapeSelection;
    PictureDraftAppModel& m_pictureDraft;
    ICommandStorage& m_commandStorage;
};

#endif //LAB10_DELETESHAPEUSECASE_H
