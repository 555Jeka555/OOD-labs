#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
    void Fly() override
    {
        m_amountDepartures++;
        std::cout << "I'm flying with wings!! Departure number:" << m_amountDepartures << std::endl;
    }

private:
    int m_amountDepartures = 0;
};

#endif