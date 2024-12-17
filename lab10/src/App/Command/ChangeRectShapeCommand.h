#ifndef LAB10_CHANGERECTSHAPECOMMAND_H
#define LAB10_CHANGERECTSHAPECOMMAND_H

#pragma once
#include "AbstractCommand.h"
#include "../../Common/Rect.h"
#include "../Model/ShapeSelection.h"
#include "../Model/ShapeApp.h"

class ChangeRectShapeCommand : public AbstractCommand
{
public:
    ChangeRectShapeCommand(
            const std::shared_ptr<ShapeApp>& shape,
            ShapeSelection& selectionModel)
        :   m_frame(shape->GetFrame()),
            m_target(shape),
            m_shapeSelection(selectionModel)
    {
    }

protected:
    void DoExecute() override
    {
        SwapFrame();
        m_shapeSelection.SetSelectedShapes({ m_target });
    }

    void DoUnexecute() override
    {
        SwapFrame();
        m_shapeSelection.SetSelectedShapes({ m_target });
    }

    void SwapFrame()
    {
        auto lastFrame = m_target->GetShape()->GetFrame();
        m_target->GetShape()->SetFrame(m_frame);

        m_frame = lastFrame;
    }
    
private:
    RectD m_frame;
    std::shared_ptr<ShapeApp> m_target;
    ShapeSelection& m_shapeSelection;

};

#endif //LAB10_CHANGERECTSHAPECOMMAND_H
