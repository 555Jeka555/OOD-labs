#ifndef LAB10_PICTUREDRAFTAPP_H
#define LAB10_PICTUREDRAFTAPP_H

#pragma once
#include <boost/signals2.hpp>
#include "ShapeApp.h"
#include "../../Model/PictureDraft.h"

class PictureDraftApp
{
public:
    PictureDraftApp(const std::shared_ptr<PictureDraft>& pictureDraft, const std::shared_ptr<IHistory> history)
            : m_pictureDraft(pictureDraft)
            , m_history(history)
    {
        m_pictureDraft->DoOnShapeAdded([&, this](size_t index) {
            auto shapeAppModel = std::make_shared<ShapeApp>(m_pictureDraft->GetShape(index));
            m_shapesApp.insert(m_shapesApp.begin() + index, shapeAppModel);
            m_shapeAdded(index);
        });

        m_pictureDraft->DoOnShapeDeleted([&, this](size_t index, const std::shared_ptr<Shape>& shape) {
            auto shapeAppModel = m_shapesApp.at(index);
            m_shapesApp.erase(m_shapesApp.begin() + index);
            m_shapeDeleted(index, shapeAppModel);
        });

        auto shapeSize = m_pictureDraft->GetShapeCount();
        for (size_t i = 0; i < shapeSize; ++i)
        {
            auto shape = m_pictureDraft->GetShape(i);
            auto shapeAppModel = std::make_shared<ShapeApp>(shape);
            m_shapesApp.push_back(shapeAppModel);
        }
    }

    [[nodiscard]] std::shared_ptr<PictureDraft> GetPictureDraft() const
    {
        return m_pictureDraft;
    }

    [[nodiscard]] size_t GetShapeCount() const
    {
        return m_shapesApp.size();
    }

    [[nodiscard]] std::shared_ptr<ShapeApp> GetShape(size_t index) const
    {
        return m_shapesApp.at(index);
    }

    connection DoOnShapeAdded(const std::function<void(size_t index)>& handler)
    {
        return m_shapeAdded.connect(handler);
    }

    connection DoOnShapeDeleted(const std::function<void(size_t index, std::shared_ptr<ShapeApp> shape)>& handler)
    {
        return m_shapeDeleted.connect(handler);
    }

    void Undo()
    {
        m_history->Undo();
    }

    void Redo()
    {
        m_history->Redo();
    }
private:
    std::shared_ptr<PictureDraft> m_pictureDraft;
    std::vector<std::shared_ptr<ShapeApp>> m_shapesApp;
    boost::signals2::signal<void(size_t index)> m_shapeAdded;
    boost::signals2::signal<void(size_t index, std::shared_ptr<ShapeApp>)> m_shapeDeleted;
    std::shared_ptr<IHistory> m_history;
};

#endif //LAB10_PICTUREDRAFTAPP_H
