#ifndef LAB10_INSERTSHAPECOMMAND_H
#define LAB10_INSERTSHAPECOMMAND_H

#pragma once
#include "AbstractCommand.h"
#include "../../Model/Shape.h"
#include "../../Model/PictureDraft.h"
#include "../Model/ShapeSelection.h"
#include "../Model/ShapeApp.h"

class InsertShapeCommand : public AbstractCommand
{
public:
    InsertShapeCommand(
            size_t index,
            const std::shared_ptr<Shape>& shape,
            const std::shared_ptr<PictureDraft>& pictureDraft,
            ShapeSelection& selection
            )
    : m_index(index)
    , m_shape(shape)
    , m_pictureDraft(pictureDraft)
    , m_shapeSelection(selection)
    {}

protected:
    void DoExecute() override
    {
        m_selectedShapes = m_shapeSelection.GetSelectedShapes();
        m_pictureDraft->InsertShape(m_shape, m_index);
    }

    void DoUnexecute() override
    {
        m_pictureDraft->DeleteShape(m_index);
        m_shapeSelection.SetSelectedShapes(m_selectedShapes);
    }

private:
    std::shared_ptr<Shape> m_shape;
    std::shared_ptr<PictureDraft> m_pictureDraft;
    ShapeSelection& m_shapeSelection;
    size_t m_index;
    std::vector<std::shared_ptr<ShapeApp>> m_selectedShapes;
};

#endif //LAB10_INSERTSHAPECOMMAND_H
