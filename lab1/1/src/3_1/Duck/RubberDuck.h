#ifndef INC_1_RUBBERDUCK_H
#define INC_1_RUBBERDUCK_H

#include "../Duck.h"
#include "../DuckFunctions.h"

class RubberDuck : public Duck
{
public:
    RubberDuck()
            : Duck(CreateFlyNoWay(), CreateSqueak(), CreateNoDance())
    {
    }

    void Display() const override
    {
        std::cout << "I'm rubber duck" << std::endl;
    }
};


#endif //INC_1_RUBBERDUCK_H
