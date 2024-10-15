#ifndef LAB4_IDESIGNER_H
#define LAB4_IDESIGNER_H

#include "../PictureDraft/PictureDraft.h"

class IDesigner
{
public:
    virtual PictureDraft CreateDraft(std::istream & inputData) = 0;

    // TODO зачем тут виртуальный дисктруктор и какие альтернативы
    virtual ~IDesigner() = default;
};

#endif //LAB4_IDESIGNER_H
