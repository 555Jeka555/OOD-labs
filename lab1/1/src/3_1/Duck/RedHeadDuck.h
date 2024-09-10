#ifndef INC_1_REDHEADDUCK_H
#define INC_1_REDHEADDUCK_H

#include "../Duck.h"
#include "../DuckFunctions.h"

class RedHeadDuck : public Duck
{
public:
    RedHeadDuck()
            : Duck(CreateFlyWithCounting(), CreateQuackNormal(), CreateDanceMinuet())
    {
    }

    void Display() const override
    {
        std::cout << "I'm redhead duck" << std::endl;
    }
};

#endif //INC_1_REDHEADDUCK_H
