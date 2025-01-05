#ifndef EXAM_DECORATORMULT_H
#define EXAM_DECORATORMULT_H

#include "Decorator.h"

class DecoratorMult : public Decorator
{
public:
    explicit DecoratorMult(IComponent& component) : Decorator(component) {}

protected:
    std::optional<double> AddToStoredByDecorator() override
    {
        return std::nullopt;
    }

    std::optional<double> MulToStoredByDecorator() override
    {
        return std::optional<double>(2);
    }
};

#endif //EXAM_DECORATORMULT_H
