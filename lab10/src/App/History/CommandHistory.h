#ifndef LAB10_COMMANDHISTORY_H
#define LAB10_COMMANDHISTORY_H

#pragma once
#include <deque>

#include "IHistory.h"
#include "ICommandStorage.h"

class CommandHistory : public IHistory, public ICommandStorage {
public:
    const size_t COMMANDS_DEPTH_LEVEL = 5;

    [[nodiscard]] bool CanUndo() const override {
        return m_nextCommandIndex > 0;
    }

    [[nodiscard]] bool CanRedo() const override
    {
        return m_nextCommandIndex < m_commands.size();
    }

    void Undo() override
    {
        if (CanUndo())
        {
            m_commands[m_nextCommandIndex - 1]->Unexecute();
            --m_nextCommandIndex;
        }
    }

    void Redo() override
    {
        if (CanRedo())
        {
            m_commands[m_nextCommandIndex]->Execute();
            ++m_nextCommandIndex;
        }
    }

    void AddAndExecuteCommand(ICommandPtr&& command) override
    {
        //стираем те команды, которые могли бы быть перевыполнены с помощью redo
        if (CanRedo())
        {
            command->Execute();
            ++m_nextCommandIndex;
            m_commands.resize(m_nextCommandIndex);
            m_commands.back() = std::move(command);

            return;
        }

        //иначе расширяем историю команд
        m_commands.emplace_back(nullptr);
        try
        {
            command->Execute();

            m_commands.back() = std::move(command);
            if (COMMANDS_DEPTH_LEVEL < m_commands.size())
            {
                m_commands.pop_front();
            }
            else
            {
                ++m_nextCommandIndex;
            }
        }
        catch (...)
        {
            m_commands.pop_back();
            throw;
        }
    }

private:
    std::deque<ICommandPtr> m_commands;
    size_t m_nextCommandIndex = 0;
};

#endif //LAB10_COMMANDHISTORY_H
