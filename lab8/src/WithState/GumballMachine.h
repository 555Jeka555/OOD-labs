#ifndef LAB8_GUMBALLMACHINE_H
#define LAB8_GUMBALLMACHINE_H

#include <iostream>
#include <format>
#include "IGumballMachine.h"
#include "State/IState.h"
#include "State/SoldState.h"
#include "State/SoldOutState.h"
#include "State/NoQuarterState.h"
#include "State/HasQuarterState.h"

class GumballMachine : private IGumballMachine
{
public:
    explicit GumballMachine(unsigned numBalls)
            : m_soldState(*this)
            , m_soldOutState(*this)
            , m_noQuarterState(*this)
            , m_hasQuarterState(*this)
            , m_state(&m_soldOutState)
            , m_count(numBalls)
    {
        if (m_count > 0)
        {
            m_state = &m_noQuarterState;
        }
    }

    void EjectQuarter()
    {
        m_state->EjectQuarter();
    }

    void InsertQuarter()
    {
        m_state->InsertQuarter();
    }

    void TurnCrank()
    {
        m_state->TurnCrank();
        m_state->Dispense();
    }

    [[nodiscard]] std::string ToString()const
    {
        return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)",
    m_count,
    m_count != 1 ? "s" : "", m_state->ToString()
    );
    }

private:
    [[nodiscard]] unsigned GetBallCount() const override
    {
        return m_count;
    }

    void ReleaseBall() override
    {
        if (m_count != 0)
        {
            std::cout << "A gumball comes rolling out the slot...\n";
            --m_count;
        }
    }

    void SetSoldOutState() override
    {
        m_state = &m_soldOutState;
    }

    void SetNoQuarterState() override
    {
        m_state = &m_noQuarterState;
    }

    void SetSoldState() override
    {
        m_state = &m_soldState;
    }

    void SetHasQuarterState() override
    {
        m_state = &m_hasQuarterState;
    }

private:
    unsigned m_count = 0;
    SoldState m_soldState{*this};
    SoldOutState m_soldOutState{*this};
    NoQuarterState m_noQuarterState{*this};
    HasQuarterState m_hasQuarterState{*this};
    IState * m_state{};
};

#endif //LAB8_GUMBALLMACHINE_H
