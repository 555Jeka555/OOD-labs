#ifndef INC_1_MODELDUCK_H
#define INC_1_MODELDUCK_H

#include "../Duck.h"
#include "../DuckFunctions.h"

class ModelDuck : public Duck
{
public:
    ModelDuck()
            : Duck(CreateFlyNoWay(), CreateMuteQuack(), CreateNoDance())
    {
    }

    void Display() const override
    {
        std::cout << "I'm model duck" << std::endl;
    }
};

#endif //INC_1_MODELDUCK_H
