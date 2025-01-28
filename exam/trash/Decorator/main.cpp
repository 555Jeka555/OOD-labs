#include "Component.h"
#include "DecoratorAdd.h"
#include "DecoratorMult.h"

int main()
{
    Component component1;
    DecoratorAdd decoratorAdd(component1);
    std::cout << decoratorAdd.GetStored() << std::endl;
    decoratorAdd.GetAddToStored();
    decoratorAdd.GetMulToStored();

    Component component2;
    DecoratorMult decoratorMult(component2);
    std::cout << decoratorMult.GetStored() << std::endl;
    decoratorMult.GetAddToStored();
    decoratorMult.GetMulToStored();

    return 0;
}