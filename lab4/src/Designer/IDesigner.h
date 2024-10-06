#ifndef LAB4_IDESIGNER_H
#define LAB4_IDESIGNER_H

#include "PictureDraft.h"

class IDesigner
{
public:
    virtual PictureDraft CreateDraft(std::istream & inputData) = 0;
};

#endif //LAB4_IDESIGNER_H
