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
    
    std::unique_ptr<MoveShapeUseCase> CreateMoveShapeUseCase()
    {
        return std::make_unique<MoveShapeUseCase>(m_shapeSelection, m_commandStorage);
    }

    std::unique_ptr<ResizeShapeUseCase> CreateResizeShapeUseCase()
    {
        return std::make_unique<ResizeShapeUseCase>(m_shapeSelection, m_commandStorage);
    }

    std::unique_ptr<InsertShapeUseCase> CreateInsertShapeUseCase(PictureDraftApp& pictureDraftAppModel)
    {
        return std::make_unique<InsertShapeUseCase>(pictureDraftAppModel, m_shapeSelection, m_commandStorage);
    }

    std::unique_ptr<DeleteShapeUseCase> CreateDeleteShapeUseCase(PictureDraftApp& pictureDraftAppModel)
    {
        return std::make_unique<DeleteShapeUseCase>(pictureDraftAppModel, m_shapeSelection, m_commandStorage);
    }

private:
    ShapeSelection& m_shapeSelection;
    ICommandStorage& m_commandStorage;
};

#endif //LAB10_USECASEFACTORY_H
