#ifndef LAB10_GROUPCOMMAND_H
#define LAB10_GROUPCOMMAND_H

#pragma once
#include <vector>
#include "../History/AbstractCommand.h"
#include "../History/ICommand.h"

class GroupCommand : public AbstractCommand
{
public:

    void AddCommand(std::unique_ptr<ICommand>&& command)
    {
        m_commands.push_back(std::move(command));
    }

protected:
    void DoExecute() override
    {
        for (auto&& command : m_commands)
        {
            command->Execute();
        }
    }

    void DoUnexecute() override
    {
        for (auto&& command : m_commands)
        {
            command->Unexecute();
        }
    }

private:
    std::vector<ICommandPtr> m_commands;
};

#endif //LAB10_GROUPCOMMAND_H
