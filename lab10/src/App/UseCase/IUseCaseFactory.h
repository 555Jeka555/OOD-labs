#ifndef LAB10_IUSECASEFACTORY_H
#define LAB10_IUSECASEFACTORY_H

#pragma once
#include <iostream>
#include <memory>
#include "../Model/PictureDraftApp.h"
#include "MoveShapeUseCase.h"
#include "ResizeShapeUseCase.h"
#include "InsertShapeUseCase.h"
#include "DeleteShapeUseCase.h"

class IUseCaseFactory
{
public:
    virtual std::unique_ptr<MoveShapeUseCase> CreateMoveShapeUseCase() = 0;
    virtual std::unique_ptr<ResizeShapeUseCase> CreateResizeShapeUseCase() = 0;
    virtual std::unique_ptr<InsertShapeUseCase> CreateInsertShapeUseCase(PictureDraftApp& pictureDraftApp) = 0;
    virtual std::unique_ptr<DeleteShapeUseCase> CreateDeleteShapeUseCase(PictureDraftApp& pictureDraftApp) = 0;

    virtual ~IUseCaseFactory() = default;
};

#endif //LAB10_IUSECASEFACTORY_H
