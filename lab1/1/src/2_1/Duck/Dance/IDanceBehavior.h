#ifndef INC_1_IDANCEBEHAVIOR_H
#define INC_1_IDANCEBEHAVIOR_H

struct IDanceBehavior
{
    virtual ~IDanceBehavior(){};
    virtual void Dance() = 0;
};


#endif //INC_1_IDANCEBEHAVIOR_H
