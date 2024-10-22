#include "MacroCommand.h"

void MacroCommand::DoExecute()
{
    for (const auto& command : m_commands)
    {
        command();
    }
}

void MacroCommand::DoUnexecute()
{
}

void MacroCommand::AddCommand(const std::function<void()>& command)
{
    m_commands.push_back(command);
}
