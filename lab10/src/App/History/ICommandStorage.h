#ifndef LAB10_ICOMMONSTORAGE_H
#define LAB10_ICOMMONSTORAGE_H

#pragma once
#include "../Command/ICommand.h"

class ICommandStorage
{
public:
    virtual void AddAndExecuteCommand(ICommandPtr&&) = 0;
};

#endif //LAB10_ICOMMONSTORAGE_H
