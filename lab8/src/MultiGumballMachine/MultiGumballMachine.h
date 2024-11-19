#ifndef LAB8_MULTIGUMBALLMACHINE_H
#define LAB8_MULTIGUMBALLMACHINE_H

#include <iostream>
#include <format>
#include "IMultiGumballMachine.h"
#include "State/IState.h"
#include "State/SoldState.h"
#include "State/SoldOutState.h"
#include "State/NoQuarterState.h"
#include "State/HasQuarterState.h"

namespace multiGumballMachine
{
    class MultiGumballMachine : private IMultiGumballMachine
    {
    public:
        explicit MultiGumballMachine(unsigned numBalls)
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
                --m_quarter;
            }
        }

        [[nodiscard]] unsigned GetQuarterCount() const override
        {
            return m_quarter;
        }

        [[nodiscard]] unsigned GetMaxQuarterCount() const override
        {
            return MAX_QUARTER;
        }

        void AddQuarter() override
        {
            ++m_quarter;
        }

        void ReturnAllQuarters() override
        {
            std::cout << "Return all quarters\n";

            m_quarter = 0;
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
        static constexpr unsigned MAX_QUARTER = 5;
        unsigned m_count = 0;
        unsigned m_quarter = 0;
        multiGumballMachine::SoldState m_soldState{*this};
        multiGumballMachine::SoldOutState m_soldOutState{*this};
        multiGumballMachine::NoQuarterState m_noQuarterState{*this};
        multiGumballMachine::HasQuarterState m_hasQuarterState{*this};
        IState * m_state{};
    };
}

#endif //LAB8_MULTIGUMBALLMACHINE_H
