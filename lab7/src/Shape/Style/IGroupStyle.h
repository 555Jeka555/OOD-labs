#ifndef LAB7_IGROUPSTYLE_H
#define LAB7_IGROUPSTYLE_H

#include "IStyle.h"
#include "IStyles.h"

class IGroupStyle : public IStyle, public IStyles
{
public:
    virtual ~IGroupStyle() = default;
};

#endif //LAB7_IGROUPSTYLE_H
