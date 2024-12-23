#ifndef LAB8_ISTATE_H
#define LAB8_ISTATE_H

#include <iostream>

class IState
{
public:
    virtual void InsertQuarter() = 0;
    virtual void EjectQuarter() = 0;
    virtual void TurnCrank() = 0;
    virtual void Dispense() = 0;
    [[nodiscard]] virtual std::string ToString()const = 0;
    virtual ~IState() = default;
};

#endif //LAB8_ISTATE_H
