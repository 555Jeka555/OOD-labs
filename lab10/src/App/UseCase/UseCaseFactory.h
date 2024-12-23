#ifndef LAB10_USECASEFACTORY_H
#define LAB10_USECASEFACTORY_H

#pragma once

#include "IUseCaseFactory.h"

class UseCaseFactory : public IUseCaseFactory
{
public:
    UseCaseFactory(ShapeSelection& shapeSelection, ICommandStorage& commandsContainer)
        :    m_shapeSelection(shapeSelection),
            m_commandStorage(commandsContainer)
    {}
    
    std::unique_ptr<IMoveShapeUseCase> CreateMoveShapeUseCase() override
    {
        return std::make_unique<MoveShapeUseCase>(m_shapeSelection, m_commandStorage);
    }

    std::unique_ptr<IResizeShapeUseCase> CreateResizeShapeUseCase() override
    {
        return std::make_unique<ResizeShapeUseCase>(m_shapeSelection, m_commandStorage);
    }

    std::unique_ptr<IInsertShapeUseCase> CreateInsertShapeUseCase(PictureDraftAppModel& pictureDraftAppModel) override
    {
        return std::make_unique<InsertShapeUseCase>(pictureDraftAppModel, m_shapeSelection, m_commandStorage);
    }

    std::unique_ptr<IDeleteShapeUseCase> CreateDeleteShapeUseCase(PictureDraftAppModel& pictureDraftAppModel) override
    {
        return std::make_unique<DeleteShapeUseCase>(pictureDraftAppModel, m_shapeSelection, m_commandStorage);
    }

private:
    IShapeSelection& m_shapeSelection;
    ICommandStorage& m_commandStorage;
};

#endif //LAB10_USECASEFACTORY_H
