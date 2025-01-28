#ifndef EXAM_DECORATOR_H
#define EXAM_DECORATOR_H

#include <optional>
#include "IComponent.h"

class Decorator : public IComponent
{
public:
    double GetStored() override {
        return m_component.GetStored();
    }

    void GetAddToStored() override {
        m_component.GetAddToStored();

        auto addToStored = AddToStoredByDecorator();
        if (addToStored.has_value())
        {
            std::cout << m_component.GetStored() + addToStored.value() << std::endl;
        }
        else
        {
            std::cout << m_component.GetStored() << std::endl;
        }
    }

    void GetMulToStored() override {
        m_component.GetMulToStored();

        auto multToStored = MulToStoredByDecorator();
        if (multToStored.has_value())
        {
            std::cout << m_component.GetStored() * multToStored.value() << std::endl;
        }
        else
        {
            std::cout << m_component.GetStored() << std::endl;
        }
    }

    virtual std::optional<double> AddToStoredByDecorator() = 0;
    virtual std::optional<double> MulToStoredByDecorator() = 0;

protected:
    explicit Decorator(IComponent& component) : m_component(component) {}

private:
    IComponent & m_component;
};

#endif //EXAM_DECORATOR_H
