#ifndef LAB10_SHAPESELECTION_H
#define LAB10_SHAPESELECTION_H

#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "ShapeApp.h"

class ShapeSelection
{
public:
    std::vector<std::shared_ptr<ShapeApp>> GetSelectedShapes() const
    {
        return m_selectedShapes;
    }

    void SetSelectedShapes(const std::vector<std::shared_ptr<ShapeApp>>& shapes)
    {
        m_selectedShapes = shapes;
        m_selectionChanged(shapes);
    }

    boost::signals2::connection DoOnSelectionChanged(const std::function<void(const std::vector<std::shared_ptr<ShapeApp>>&)>& handler)
    {
        return m_selectionChanged.connect(handler);
    }

private:
    std::vector<std::shared_ptr<ShapeApp>> m_selectedShapes;
    boost::signals2::signal<void(const std::vector<std::shared_ptr<ShapeApp>>&)> m_selectionChanged;
};

#endif //LAB10_SHAPESELECTION_H
