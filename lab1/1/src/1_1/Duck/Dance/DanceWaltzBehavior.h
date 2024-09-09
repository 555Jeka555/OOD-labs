#ifndef INC_1_DANCEWALTZBEHAVIOR_H
#define INC_1_DANCEWALTZBEHAVIOR_H

#include "IDanceBehavior.h"
#include "iostream"

class DanceWaltzBehavior : public IDanceBehavior
{
public:
    void Dance() override
    {
        std::cout << "Waltz!!" << std::endl;
    }
};

#endif //INC_1_DANCEWALTZBEHAVIOR_H
