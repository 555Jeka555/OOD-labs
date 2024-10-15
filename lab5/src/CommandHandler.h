#ifndef LAB5_COMMANDHANDLER_H
#define LAB5_COMMANDHANDLER_H

#include <sstream>
#include "Menu/Menu.h"
#include "Document/IDocument.h"
#include "Document/Command/HelpCommand/HelpCommand.h"

class CommandHandler
{
public:
    CommandHandler(Menu & menu, IDocument & document)
        : m_menu(menu), m_document(document)
    {}

    void Handle(std::istream & inputData)
    {
        std::string line;
        while (getline(inputData, line))
        {
            std::istringstream iss(line);
            std::string name;
            iss >> name;

            if (name == HelpCommand::name)
            {
                m_menu.AddItem(HelpCommand::name, "Help", [&](std::istream &args) {
                    HelpCommand helpCommand;
                    helpCommand.Execute();
                });
            }
        }
    }

private:
    Menu & m_menu;
    IDocument & m_document;
};

#endif //LAB5_COMMANDHANDLER_H
