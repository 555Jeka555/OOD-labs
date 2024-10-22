#ifndef LAB5_COMMANDHANDLER_H
#define LAB5_COMMANDHANDLER_H

#include <sstream>
#include "Menu/Menu.h"
#include "Document/IDocument.h"

class CommandHandler
{
public:
    CommandHandler(Menu & menu, IDocument & document)
        : m_menu(menu), m_document(document)
    {
        m_menu.AddItem("Help", "Help", [this](std::istream&) { m_menu.ShowInstructions(); });
        AddMenuItem("BeginMacro", "BeginMacro Macro Description", &CommandHandler::BeginMacro);
        AddMenuItem("EndMacro", "EndMacro", &CommandHandler::EndMacro);
        AddMenuItem(InsertParagraphCommand::name, "InsertParagraph end aaa", &CommandHandler::InsertParagraph);
        AddMenuItem("List", "Show document", &CommandHandler::List);
        AddMenuItem(SetTitleCommand::name, "Set title", &CommandHandler::SetTitle);
        AddMenuItem(ReplaceTextCommand::name, "ReplaceText 0 text", &CommandHandler::ReplaceText);
        AddMenuItem(DeleteItemCommand::name, "DeleteItem 0", &CommandHandler::DeleteItem);
        AddMenuItem("Undo", "Undo command", &CommandHandler::Undo);
        AddMenuItem("Redo", "Redo command", &CommandHandler::Redo);
        AddMenuItem("Save", "Save save.html", &CommandHandler::Save);
        AddMenuItem(InsertImageCommand::name, "InsertImage end 100 200 C:\\Volgatech\\3course\\OOD-labs\\lab5\\1.png", &CommandHandler::InsertImage);
        AddMenuItem(ResizeImageCommand::name, "ResizeImage 0 400 500", &CommandHandler::ResizeImage);
    }

private:
    Menu & m_menu;
    IDocument & m_document;

    typedef void (CommandHandler::*MenuHandler)(std::istream & in);
    void AddMenuItem(const std::string & shortcut, const std::string & description, MenuHandler handler)
    {
        m_menu.AddItem(shortcut, description, bind(handler, this, std::placeholders::_1));
    }

    void BeginMacro(std::istream &in)
    {
        std::string nameMacro;
        std::string descMacro;

        in >> nameMacro >> descMacro;

        if (m_menu.IsRecordMacro()) {
            throw std::invalid_argument("Already recording a macro.");
        }

        m_menu.SetCurrentMacro(std::make_shared<MacroCommand>(nameMacro, descMacro));
        std::cout << "Recording a new macro " << nameMacro << "..." << std::endl;
    }

    void EndMacro(std::istream &)
    {
        if (!m_menu.IsRecordMacro()) {
            throw std::invalid_argument("No macro is currently being recorded.");
        }

        m_menu.AddCurrentMacroMenuItem();
        std::cout << "Macro saved" << std::endl;
    }

    void RecordCommand(std::function<void()> command) {
        if (m_menu.IsRecordMacro())
        {
            m_menu.AddCommandToCurrentMacro(command);
        }
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
                std::cout << (i + 1) << ". Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << "\n";
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

        if (m_menu.IsRecordMacro())
        {
            RecordCommand([this, text, position]() {
                m_document.InsertParagraph(text, position);
                std::cout << "Inserted Paragraph" << std::endl;
            });
        }
        else
        {
            m_document.InsertParagraph(text, position);
        }
    }

    void SetTitle(std::istream & in)
    {
        std::string title;

        in >> title;

        if (m_menu.IsRecordMacro())
        {
            RecordCommand([this, title]() {
                m_document.SetTitle(title);
                std::cout << "Set Title" << std::endl;
            });
        }
        else
        {
            m_document.SetTitle(title);
        }
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

        if (m_menu.IsRecordMacro())
        {
            RecordCommand([this, newText, position]() {
                m_document.ReplaceText(newText, position);
                std::cout << "Replace Text" << std::endl;
            });
        }
        else
        {
            m_document.ReplaceText(newText, position);
        }
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

        if (m_menu.IsRecordMacro())
        {
            RecordCommand([this, position]() {
                m_document.DeleteItem(position);
                std::cout << "Delete Item" << std::endl;
            });
        }
        else
        {
            m_document.DeleteItem(position);
        }
    }

    void Undo(std::istream &)
    {
        if (m_document.CanUndo())
        {
            if (m_menu.IsRecordMacro())
            {
                RecordCommand([this]() {
                    m_document.Undo();
                    std::cout << "Undo" << std::endl;
                });
            }
            else
            {
                m_document.Undo();
            }
        }
        else
        {
            std::cout << "Can't undo" << std::endl;
        }
    }

    void Redo(std::istream &)
    {
        if (m_document.CanRedo())
        {
            if (m_menu.IsRecordMacro())
            {
                RecordCommand([this]() {
                    m_document.Redo();
                    std::cout << "Redo" << std::endl;
                });
            }
            else
            {
                m_document.Redo();
            }
        }
        else
        {
            std::cout << "Can't redo" << std::endl;
        }
    }

    void Save(std::istream & in)
    {
        std::string path;

        in >> path;

        if (m_menu.IsRecordMacro())
        {
            RecordCommand([this, path]() {
                m_document.Save(path);
                std::cout << "Save" << std::endl;
            });
        }
        else
        {
            m_document.Save(path);
        }
    }

    void InsertImage(std::istream & in)
    {
        std::string path;
        std::string widthStr;
        std::string heightStr;
        std::string positionStr;

        in >> positionStr >> widthStr >> heightStr >> path;

        int width, height;
        try
        {
            width = std::stoi(widthStr);
            height = std::stoi(heightStr);
        }
        catch (...)
        {
            throw std::invalid_argument("Invalid width or height");
        }

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

        if (m_menu.IsRecordMacro())
        {
            RecordCommand([this, path, width, height, position]() {
                m_document.InsertImage(path, width, height, position);
                std::cout << "InsertImage" << std::endl;
            });
        }
        else
        {
            m_document.InsertImage(path, width, height, position);
        }
    }

    void ResizeImage(std::istream & in)
    {
        std::string widthStr;
        std::string heightStr;
        std::string positionStr;

        in >> positionStr >> widthStr >> heightStr;

        int width, height;
        try
        {
            width = std::stoi(widthStr);
            height = std::stoi(heightStr);
        }
        catch (...)
        {
            throw std::invalid_argument("Invalid width or height");
        }

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

        if (m_menu.IsRecordMacro())
        {
            RecordCommand([this, width, height, position]() {
                m_document.ResizeImage(width, height, position);
                std::cout << "ResizeImage" << std::endl;
            });
        }
        else
        {
            m_document.ResizeImage(width, height, position);
        }
    }
};

#endif //LAB5_COMMANDHANDLER_H
