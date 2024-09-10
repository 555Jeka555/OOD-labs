#ifndef INC_1_NODANCEBEHAVIOR_H
#define INC_1_NODANCEBEHAVIOR_H

#include "IDanceBehavior.h"
#include "iostream"

class NoDanceBehavior : public IDanceBehavior
{
public:
    void Dance() override {}
};

#endif //INC_1_NODANCEBEHAVIOR_H
