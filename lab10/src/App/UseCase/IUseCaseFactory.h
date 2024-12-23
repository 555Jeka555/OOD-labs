#ifndef LAB10_IUSECASEFACTORY_H
#define LAB10_IUSECASEFACTORY_H

#pragma once
#include <iostream>
#include <memory>
#include "../Model/PictureDraftAppModel.h"
#include "MoveShapeUseCase.h"
#include "ResizeShapeUseCase.h"
#include "InsertShapeUseCase.h"
#include "DeleteShapeUseCase.h"

class IUseCaseFactory
{
public:
    virtual std::unique_ptr<IMoveShapeUseCase> CreateMoveShapeUseCase() = 0;
    virtual std::unique_ptr<IResizeShapeUseCase> CreateResizeShapeUseCase() = 0;
    virtual std::unique_ptr<IInsertShapeUseCase> CreateInsertShapeUseCase(PictureDraftAppModel& pictureDraftApp) = 0;
    virtual std::unique_ptr<IDeleteShapeUseCase> CreateDeleteShapeUseCase(PictureDraftAppModel& pictureDraftApp) = 0;

    virtual ~IUseCaseFactory() = default;
};

#endif //LAB10_IUSECASEFACTORY_H
