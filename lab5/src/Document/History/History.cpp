#include <cassert>
#include "History.h"

History::History()
= default;

History::~History()
= default;

bool History::CanUndo() const
{
    return m_nextCommandIndex != 0;
}

bool History::CanRedo() const
{
    return m_nextCommandIndex != m_commands.size();
}

void History::Undo()
{
    if (CanUndo())
    {
        m_commands[m_nextCommandIndex - 1]->Unexecute();
        --m_nextCommandIndex;
    }
}

void History::Redo()
{
    if (CanRedo())
    {
        m_commands[m_nextCommandIndex]->Execute();
        ++m_nextCommandIndex;
    }
}

void History::AddAndExecuteCommand(ICommandPtr && command)
{
    if (m_nextCommandIndex < m_commands.size())
    {
        command->Execute();
        ++m_nextCommandIndex;
        m_commands.resize(m_nextCommandIndex);
        m_commands.back() = std::move(command);
    }
    else
    {
        assert(m_nextCommandIndex == m_commands.size());
        m_commands.emplace_back(nullptr);

        try
        {
            command->Execute();
            m_commands.back() = std::move(command);
            ++m_nextCommandIndex;
        }
        catch (...)
        {
            m_commands.pop_back();
            throw;
        }

    }
}

