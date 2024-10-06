#ifndef LAB4_DESIGNER_H
#define LAB4_DESIGNER_H

#include "PictureDraft.h"
#include "IDesigner.h"
#include "../Shape/Factory/IShapeFactory.h"

class Designer : public IDesigner
{
public:
    explicit Designer(IShapeFactory & factory)
    : m_factory(factory) {}

    PictureDraft CreateDraft(std::istream & inputData) override
    {
        PictureDraft draft;
        std::string line;
        while (getline(inputData, line))
        {
            draft.AddShape(m_factory.CreateShape(line));
        }
        return draft;
    }

private:
    IShapeFactory & m_factory;
};

#endif //LAB4_DESIGNER_H
