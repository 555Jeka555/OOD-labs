#ifndef LAB7_IGROUPSHAPE_H
#define LAB7_IGROUPSHAPE_H

#include "IShape.h"
#include "IShapes.h"

class IGroupShape : public IShape, public IShapes
{
public:
    virtual ~IGroupShape() = default;
};


#endif //LAB7_IGROUPSHAPE_H
