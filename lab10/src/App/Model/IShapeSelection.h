#ifndef LAB10_ISHAPESELECTION_H
#define LAB10_ISHAPESELECTION_H

#pragma once
#include "../Model/ShapeAppModel.h"

class IShapeSelection
{
public:

    [[nodiscard]] virtual std::vector<std::shared_ptr<ShapeAppModel>> GetSelectedShapes() const = 0;
    virtual void SetSelectedShapes(const std::vector<std::shared_ptr<ShapeAppModel>>& shapes) = 0;
    virtual void DoOnSelectionChanged(const std::function<void(const std::vector<std::shared_ptr<ShapeAppModel>>&)>& handler) = 0;

    ~IShapeSelection() = default;
};

#endif //LAB10_ISHAPESELECTION_H
