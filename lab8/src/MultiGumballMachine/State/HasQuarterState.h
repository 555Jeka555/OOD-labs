#ifndef LAB8_MULTIHASQUARTERSTATE_H
#define LAB8_MULTIHASQUARTERSTATE_H

#include "IState.h"
#include "../IMultiGumballMachine.h"

namespace multiGumballMachine
{
    class HasQuarterState : public IState
    {
    public:
        explicit HasQuarterState(IMultiGumballMachine & gumballMachine)
                :m_gumballMachine(gumballMachine)
        {}

        void InsertQuarter() override
        {
            if (m_gumballMachine.GetQuarterCount() < m_gumballMachine.GetMaxQuarterCount())
            {
                m_gumballMachine.AddQuarter();
                std::cout << "You inserted another quarter\n";
            }
            else
            {
                std::cout << "You can't insert another quarter\n";
            }
        }

        void EjectQuarter() override
        {
            std::cout << "All quarters returned\n";
            m_gumballMachine.ReturnAllQuarters();
            m_gumballMachine.SetNoQuarterState();
        }

        void TurnCrank() override
        {
            if (m_gumballMachine.GetQuarterCount() == 0)
            {
                std::cout << "No quarters left.\n";
                m_gumballMachine.SetSoldOutState();
            }
            else
            {
                std::cout << "You turned...\n";
                m_gumballMachine.SetSoldState();
            }
        }

        void Dispense() override
        {
            std::cout << "No gumball dispensed\n";
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "waiting for turn of crank";
        }

    private:
        IMultiGumballMachine & m_gumballMachine;
    };
}

#endif //LAB8_MULTIHASQUARTERSTATE_H
