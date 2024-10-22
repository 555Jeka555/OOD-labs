#ifndef LAB5_MACROCOMMAND_H
#define LAB5_MACROCOMMAND_H

#include <vector>
#include <functional>
#include <iostream>
#include <memory>
#include "../AbstractCommand/AbstractCommand.h"

class MacroCommand : public AbstractCommand
{
public:
    MacroCommand(const std::string & name) : m_name(name) {}

    void AddCommand(std::function<void()> command);

    [[nodiscard]] std::string GetName() const
    {
        return m_name;
    }
protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::vector<std::function<void()>> m_commands;
    std::string m_name;
};


#endif //LAB5_MACROCOMMAND_H
