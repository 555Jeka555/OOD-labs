#ifndef EXAM_ICOMPONENT_H
#define EXAM_ICOMPONENT_H

#include <memory>
#include <iostream>

class IComponent
{
public:
    virtual double GetStored() = 0;

    virtual void GetAddToStored() = 0;

    virtual void GetMulToStored() = 0;

    ~IComponent() = default;
};


#endif //EXAM_ICOMPONENT_H
