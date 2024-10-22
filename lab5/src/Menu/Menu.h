#ifndef LAB5_MENU_H
#define LAB5_MENU_H

#include <iostream>
#include <functional>
#include "../Document/Command/MacroCommand/MacroCommand.h"

class Menu {
public:
    typedef std::function<void(std::istream &args)> Command;
    void AddItem(const std::string & shortcut, const std::string & description, const Command & command);

    void Run();

    void ShowInstructions()const;

    void Exit();

    [[nodiscard]] bool IsRecordMacro() const;

    void SetCurrentMacro(std::shared_ptr<MacroCommand> currentMacro);

    void AddCommandToCurrentMacro(std::function<void()> command);

    void AddCurrentMacroMenuItem();

private:
    bool ExecuteCommand(const std::string & command);

    struct Item
    {
        Item(const std::string & shortcut, const std::string & description, const Command & command)
                : shortcut(shortcut)
                , description(description)
                , command(command)
        {}

        std::string shortcut;
        std::string description;
        Command command;
    };
    std::vector<Item> m_items;
    bool m_exit = false;
    std::vector<std::shared_ptr<MacroCommand>> m_macros;
    std::shared_ptr<MacroCommand> m_currentMacro = nullptr;
};


#endif //LAB5_MENU_H
