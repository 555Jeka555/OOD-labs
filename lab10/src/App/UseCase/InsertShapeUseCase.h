#ifndef LAB10_INSERTSHAPEUSECASE_H
#define LAB10_INSERTSHAPEUSECASE_H

#pragma once
#include "../Model/ShapeSelection.h"
#include "../Model/PictureDraftAppModel.h"
#include "../History/ICommandStorage.h"
#include "../Command/GroupCommand.h"
#include "../Command/InsertShapeCommand.h"
#include "IInsertShapeUseCase.h"

class InsertShapeUseCase : public IInsertShapeUseCase
{
public:
    InsertShapeUseCase(
            PictureDraftAppModel& pictureDraft,
            IShapeSelection& selection,
            ICommandStorage& commandStorage)
        :   m_pictureDraft(pictureDraft),
            m_commandStorage(commandStorage),
            m_shapeSelection(selection)
    {
    }

    void Execute(size_t index, ShapeType shapeType) override
    {
        auto shape = std::make_shared<Shape>(shapeType);
        auto domainPictureDraft = m_pictureDraft.GetPictureDraft();
        auto insertCommand = std::make_unique<InsertShapeCommand>(index, shape, domainPictureDraft, m_shapeSelection);
        m_commandStorage.AddAndExecuteCommand(std::move(insertCommand));
    }
private:
    IShapeSelection& m_shapeSelection;
    PictureDraftAppModel& m_pictureDraft;
    ICommandStorage& m_commandStorage;
};

#endif //LAB10_INSERTSHAPEUSECASE_H
