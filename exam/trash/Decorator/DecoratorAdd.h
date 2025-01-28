#ifndef EXAM_DECORATORADD_H
#define EXAM_DECORATORADD_H

#include "Decorator.h"

class DecoratorAdd : public Decorator
{
public:
    explicit DecoratorAdd(IComponent& component) : Decorator(component) {}

protected:
    std::optional<double> AddToStoredByDecorator() override
    {
        return std::optional<double>(3);
    }

    std::optional<double> MulToStoredByDecorator() override
    {
        return std::nullopt;
    }
};

#endif //EXAM_DECORATORADD_H
