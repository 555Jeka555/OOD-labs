#ifndef INC_1_MALLARDDUCK_H
#define INC_1_MALLARDDUCK_H

#include "../Duck.h"
#include "../DuckFunctions.h"

class MallardDuck : public Duck
{
public:
    MallardDuck()
            : Duck(CreateFlyWithCounting(), CreateQuackNormal(), CreateDanceWaltz())
    {
    }

    void Display() const override
    {
        std::cout << "I'm mallard duck" << std::endl;
    }
};

#endif //INC_1_MALLARDDUCK_H
