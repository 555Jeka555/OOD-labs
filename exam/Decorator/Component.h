#ifndef EXAM_COMPONENT_H
#define EXAM_COMPONENT_H

#include "IComponent.h"

class Component : public IComponent
{
public:
    double GetStored() override
    {
        return m_store;
    }

    void GetAddToStored() override
    {
        m_store++;
    }

    void GetMulToStored() override
    {
        m_store *= 2;
    }

private:
    double m_store = 1;
};

#endif //EXAM_COMPONENT_H
