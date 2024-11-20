#ifndef LAB8_MULTISOLDSTATE_H
#define LAB8_MULTISOLDSTATE_H

#include "IState.h"
#include "../IMultiGumballMachine.h"

namespace multiGumballMachine
{
    class SoldState : public IState
    {
    public:
        explicit SoldState(IMultiGumballMachine & gumballMachine)
                :m_gumballMachine(gumballMachine)
        {}

        void InsertQuarter() override
        {
            std::cout << "Please wait, we're already giving you a gumball\n";
        }

        void EjectQuarter() override
        {
            std::cout << "Sorry you already turned the crank\n";
        }

        void TurnCrank() override
        {
            std::cout << "Turning twice doesn't get you another gumball\n";
        }

        void Dispense() override
        {
            m_gumballMachine.ReleaseBall();
            if (m_gumballMachine.GetBallCount() == 0)
            {
                std::cout << "Oops, out of gumballs\n";
                if (m_gumballMachine.GetQuarterCount() > 0)
                {
                    // TODO не проверяется
                    m_gumballMachine.ReturnAllQuarters();
                }
                m_gumballMachine.SetSoldOutState();
            }
            else if (m_gumballMachine.GetQuarterCount() > 0)
            {
                m_gumballMachine.SetHasQuarterState();
            }
            else
            {
                m_gumballMachine.SetNoQuarterState();
            }
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "delivering a gumball";
        }

    private:
        IMultiGumballMachine & m_gumballMachine;
    };
}

#endif //LAB8_MULTISOLDSTATE_H
