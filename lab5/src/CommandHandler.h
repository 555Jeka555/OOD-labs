#ifndef LAB5_COMMANDHANDLER_H
#define LAB5_COMMANDHANDLER_H

#include <sstream>
#include "Menu/Menu.h"
#include "Document/IDocument.h"

class CommandHandler
{
public:
    CommandHandler(Menu & menu, Document & document)
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

            if (name == "Help")
            {
                m_menu.AddItem("Help", "Help", [this](std::istream&) { m_menu.ShowInstructions(); });
            }
            else if (name == InsertParagraphCommand::name)
            {
                AddMenuItem(InsertParagraphCommand::name, "InsertParagraph", &CommandHandler::InsertParagraph);
            }
            else if (name == "List")
            {
                m_menu.AddItem("List", "Show document", std::bind(&CommandHandler::List, this, std::placeholders::_1));
            }
            else if (name == SetTitleCommand::name)
            {
                AddMenuItem(SetTitleCommand::name, "Set title", &CommandHandler::SetTitle);
            }
            else if (name == ReplaceTextCommand::name)
            {
                AddMenuItem(ReplaceTextCommand::name, "Replace text", &CommandHandler::ReplaceText);
            }
            else if (name == DeleteItemCommand::name)
            {
                AddMenuItem(DeleteItemCommand::name, "Delete item", &CommandHandler::DeleteItem);
            }
        }
    }

private:
    Menu & m_menu;
    Document & m_document;

    typedef void (CommandHandler::*MenuHandler)(std::istream & in);
    void AddMenuItem(const std::string & shortcut, const std::string & description, MenuHandler handler)
    {
        m_menu.AddItem(shortcut, description, bind(handler, this, std::placeholders::_1));
    }

    void List(std::istream &)
    {
        std::cout << "Title " << m_document.GetTitle() << "\n";

        for (int i = 0; i < m_document.GetItemsCount(); i++)
        {
            auto documentItem = m_document.GetItem(i);
            auto paragraph = documentItem.GetParagraph();
            if (paragraph != nullptr)
            {
                std::cout << (i + 1) << ". Paragrpah: " << paragraph->GetText() << "\n";
            }

            auto image = documentItem.GetImage();
            if (image != nullptr)
            {
                std::cout<< (i + 1) << ". Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << "\n";
            }
        }
    }

    void InsertParagraph(std::istream & in)
    {
        std::string text;
        std::string positionStr;

        in >> positionStr >> text;

        std::optional<size_t> position;
        if (positionStr == "end")
        {
            position = std::nullopt;
        }
        else
        {
            try
            {
                position = std::stoi(positionStr);
            }
            catch (...)
            {
                throw std::invalid_argument("Invalid type position");
            }
        }

        m_document.InsertParagraph(text, position);
    }

    void SetTitle(std::istream & in)
    {
        std::string title;

        in >> title;

        m_document.SetTitle(title);
    }

    void ReplaceText(std::istream & in)
    {
        std::string newText;
        std::string positionStr;

        in >> positionStr >> newText;

        std::optional<size_t> position;
        try
        {
            position = std::stoi(positionStr);
        }
        catch (...)
        {
            throw std::invalid_argument("Invalid type position");
        }

        m_document.ReplaceText(newText, position);
    }

    void DeleteItem(std::istream & in)
    {
        std::string positionStr;

        in >> positionStr;

        size_t position;
        try
        {
            position = std::stoi(positionStr);
        }
        catch (...)
        {
            throw std::invalid_argument("Invalid type position");
        }

        m_document.DeleteItem(position);
    }
};

#endif //LAB5_COMMANDHANDLER_H
