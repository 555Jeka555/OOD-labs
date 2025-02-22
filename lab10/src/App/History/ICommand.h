#ifndef LAB10_ICOMMAND_H
#define LAB10_ICOMMAND_H

#pragma once
#include <memory>

class ICommand
{
public:
    virtual void Execute() = 0;
    virtual void Unexecute() = 0;

    virtual ~ICommand() = default;
};

typedef std::unique_ptr<ICommand> ICommandPtr;

#endif //LAB10_ICOMMAND_H
