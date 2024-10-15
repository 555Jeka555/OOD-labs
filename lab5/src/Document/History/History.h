#ifndef LAB5_HISTORY_H
#define LAB5_HISTORY_H

#include "../Command/ICommand_fwd.h"
#include "../Command/ICommand.h"
#include <deque>

class History
{
public:
    History();
    ~History();

    [[nodiscard]] bool CanUndo()const;
    void Undo();
    [[nodiscard]] bool CanRedo()const;
    void Redo();
    void AddAndExecuteCommand(ICommandPtr && command);
private:
    std::deque<ICommandPtr> m_commands;
    size_t m_nextCommandIndex = 0;
};

#endif //LAB5_HISTORY_H
