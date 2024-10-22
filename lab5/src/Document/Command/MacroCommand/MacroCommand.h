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
    MacroCommand(const std::string & name, const std::string & description) : m_name(name), m_description(description) {}

    void AddCommand(const std::function<void()>& command);

    [[nodiscard]] std::string GetName() const
    {
        return m_name;
    }

    [[nodiscard]] std::string GetDescription() const
    {
        return m_description;
    }
protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::vector<std::function<void()>> m_commands;
    std::string m_name;
    std::string m_description;
};


#endif //LAB5_MACROCOMMAND_H
