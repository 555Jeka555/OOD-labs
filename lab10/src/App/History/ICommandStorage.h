#ifndef LAB10_ICOMMONSTORAGE_H
#define LAB10_ICOMMONSTORAGE_H

#pragma once
#include "ICommand.h"

class ICommandStorage
{
public:
    virtual void AddAndExecuteCommand(ICommandPtr&& command) = 0;
};

#endif //LAB10_ICOMMONSTORAGE_H
