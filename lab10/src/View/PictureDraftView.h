#ifndef LAB10_PICTUREDRADTVIEW_H
#define LAB10_PICTUREDRADTVIEW_H

#pragma once
#include <iostream>
#include "../App/Model/ShapeSelection.h"
#include "../App/Model/PictureDraftAppModel.h"
#include "../Canvas/ICanvas.h"
#include "SelectionFrameView.h"
#include "ShapeView.h"

class PictureDraftView
{
public:
    PictureDraftView(IShapeSelection& shapeSelection, size_t width, size_t height)
            :   m_shapeSelection(shapeSelection),
                m_width(width),
                m_height(height)
    {
        m_shapeSelection.DoOnSelectionChanged([&, this](const std::vector<std::shared_ptr<ShapeAppModel>>& selectedShapes) mutable {
            m_selectionFramesView.clear();
            for (auto&& shape : selectedShapes)
            {
                m_selectionFramesView.push_back(SelectionFrameView(*shape));
            }
        });
    }

    void Draw(ICanvas& canvas)
    {
        for (auto&& shape : m_shapesView)
        {
            shape->Draw(canvas);
        }

        for (auto&& selectionFrame : m_selectionFramesView)
        {
            selectionFrame.Draw(canvas);
        }
    }

    void InsertShapeView(size_t index, std::shared_ptr<ShapeView>&& shapeView)
    {
        m_shapesView.insert(m_shapesView.begin() + index, std::move(shapeView));
    }

    void DeleteShapeView(size_t index)
    {
        m_shapesView.erase(m_shapesView.begin() + index);
    }

    [[nodiscard]] size_t GetShapeViewCount() const
    {
        return m_shapesView.size();
    }

    [[nodiscard]] size_t GetWidth() const
    {
        return m_width;
    }

    [[nodiscard]] size_t GetHeight() const
    {
        return m_height;
    }

private:
    std::vector<std::shared_ptr<ShapeView>> m_shapesView;
    std::vector<SelectionFrameView> m_selectionFramesView;
    IShapeSelection& m_shapeSelection;
    size_t m_width;
    size_t m_height;
};

#endif //LAB10_PICTUREDRADTVIEW_H
