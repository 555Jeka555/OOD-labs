#ifndef LAB10_DELETESHAPECOMMAND_H
#define LAB10_DELETESHAPECOMMAND_H

#pragma once
#include "AbstractCommand.h"
#include "../../Model/Shape.h"
#include "../../Model/PictureDraft.h"
#include "../Model/ShapeSelection.h"

class DeleteShapeCommand : public AbstractCommand
{
public:
    DeleteShapeCommand(
            const std::shared_ptr<Shape>& shape,
            const std::shared_ptr<PictureDraft>& pictureDraft,
            ShapeSelection& selection)
    : m_shape(shape)
    , m_pictureDraft(pictureDraft)
    , m_shapeSelection(selection)
    {
        auto size = m_pictureDraft->GetShapeCount();
        auto shapeId = m_shape->GetId();
        for (size_t i = 0; i < size; ++i)
        {
            if (shapeId == m_pictureDraft->GetShape(i)->GetId())
            {
                m_index = i;
                break;
            }
        }
    }

protected:
    void DoExecute() override
    {
        m_selectedShapes = m_shapeSelection.GetSelectedShapes();
        m_pictureDraft->DeleteShape(m_index);
    }

    void DoUnexecute() override
    {
        m_pictureDraft->InsertShape(m_shape, m_index);
        m_shapeSelection.SetSelectedShapes(m_selectedShapes);
    }

private:
    std::shared_ptr<Shape> m_shape;
    std::shared_ptr<PictureDraft> m_pictureDraft;
    ShapeSelection& m_shapeSelection;
    std::vector<std::shared_ptr<ShapeApp>> m_selectedShapes;
    size_t m_index = SIZE_MAX;
};

#endif //LAB10_DELETESHAPECOMMAND_H
