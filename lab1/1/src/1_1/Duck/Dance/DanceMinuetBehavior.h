#ifndef INC_1_DANCEMINUETBEHAVIOR_H
#define INC_1_DANCEMINUETBEHAVIOR_H

#include "IDanceBehavior.h"
#include "iostream"

class DanceMinuetBehavior : public IDanceBehavior
{
public:
    void Dance() override
    {
        std::cout << "Minuet!!" << std::endl;
    }
};

#endif //INC_1_DANCEMINUETBEHAVIOR_H
