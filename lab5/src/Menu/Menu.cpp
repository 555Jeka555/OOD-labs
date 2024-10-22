#include "Menu.h"
#include <sstream>
#include <utility>

void Menu::AddItem(const std::string & shortcut, const std::string & description, const Command & command)
{
    m_items.emplace_back(shortcut, description, command);
}

void Menu::Run()
{
    ShowInstructions();

    std::string command;
    while ((std::cout << ">")
           && getline(std::cin, command)
           && !command.empty()
           && ExecuteCommand(command))
    {
    }
}

void Menu::ShowInstructions() const
{
    std::cout << "Commands list:\n";
    for (auto & item : m_items)
    {
        std::cout << "  " << item.shortcut << ": " << item.description << "\n";
    }
}

void Menu::Exit()
{
    m_exit = true;
}

bool Menu::ExecuteCommand(const std::string & command)
{
    std::istringstream iss(command);
    std::string name;
    iss >> name;

    m_exit = false;
    auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item & item) {
        return item.shortcut == name;
    });

    auto itMacro = std::find_if(m_macros.begin(), m_macros.end(), [&](std::shared_ptr<MacroCommand> & macro) {
        return macro->GetName() == name;
    });

    if (it != m_items.end())
    {
        if (Menu::IsRecordMacro() && itMacro != m_macros.end())
        {
            auto macro = *(itMacro->get());
            std::shared_ptr<MacroCommand> macroPtr = std::make_shared<MacroCommand>(macro);
            m_macrosToMacro.push_back(macroPtr);
        }
        else
        {
            it->command(iss);
        }
    }
    else
    {
        std::cout << "Unknown command\n";
    }
    return !m_exit;
}

bool Menu::IsRecordMacro() const
{
    return m_currentMacro != nullptr;
}

void Menu::SetCurrentMacro(std::shared_ptr<MacroCommand> currentMacro)
{
    m_currentMacro = std::move(currentMacro);
}

void Menu::AddCommandToCurrentMacro(const std::function<void()>& command)
{
    m_currentMacro->AddCommand(command);
}

void Menu::AddCurrentMacroMenuItem()
{
    if (Menu::IsRecordMacro())
    {
        for (const auto& macro : m_macrosToMacro)
        {
            m_currentMacro->AddCommand([macro]() {
                macro->Execute();
            });
        }

        std::shared_ptr<MacroCommand> copyMacro = m_currentMacro;

        AddItem(copyMacro->GetName(), copyMacro->GetDescription(), [copyMacro](std::istream&) {
            copyMacro->Execute();
        });

        m_macros.push_back(copyMacro);

        m_currentMacro = nullptr;
    }
}

int Menu::GetItemsCount()
{
    return static_cast<int>(m_items.size());
}
