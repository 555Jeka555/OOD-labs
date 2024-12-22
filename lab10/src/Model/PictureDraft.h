#ifndef LAB10_PICTUREDRAFT_H
#define LAB10_PICTUREDRAFT_H

#pragma once
#include <iostream>
#include <memory>
#include <boost/signals2.hpp>
#include "../Model/Shape.h"

using namespace boost::signals2;

class PictureDraft
{
public:
    [[nodiscard]] size_t GetShapeCount() const
    {
        return m_shapes.size();
    }

    [[nodiscard]] std::shared_ptr<Shape> GetShape(size_t index) const
    {
        return m_shapes.at(index);
    }

    void InsertShape(const std::shared_ptr<Shape>& shape, size_t index)
    {
        auto size = m_shapes.size();
        if (size < index)
        {
            throw std::out_of_range("Index out of range");
        }
        if (size == index)
        {
            m_shapes.push_back(shape);
        }
        else
        {
            m_shapes.insert(m_shapes.begin() + index, shape);
        }
        m_shapeAdded(index);
    }

    std::shared_ptr<Shape> DeleteShape(size_t index)
    {
        auto shapeToDelete = m_shapes.at(index);
        m_shapes.erase(m_shapes.begin() + index);
        m_shapeDeleted(index, shapeToDelete);

        return shapeToDelete;
    }

    void DoOnShapeAdded(const std::function<void(size_t index)>& handler)
    {
        m_shapeAdded.connect(handler);
    }

    void DoOnShapeDeleted(const std::function<void(size_t index, const std::shared_ptr<Shape>& shape)>& handler)
    {
        m_shapeDeleted.connect(handler);
    }

private:
    std::vector<std::shared_ptr<Shape>> m_shapes;
    boost::signals2::signal<void(size_t index)> m_shapeAdded;
    boost::signals2::signal<void(size_t index, const std::shared_ptr<Shape>&)> m_shapeDeleted;
};

#endif //LAB10_PICTUREDRAFT_H
