#ifndef LAB5_COMMANDHANDLER_H
#define LAB5_COMMANDHANDLER_H

#include <sstream>
#include "Menu/Menu.h"
#include "Document/IDocument.h"
#include "Document/Command/MacroCommand/MacroCommand.h"

class CommandHandler
{
public:
    CommandHandler(Menu & menu, IDocument & document)
        : m_menu(menu), m_document(document)
    {
        m_menu.AddItem("Help", "Help", [this](std::istream&) { m_menu.ShowInstructions(); });
        AddMenuItem("BeginMacro", "BeginMacro Macro", &CommandHandler::BeginMacro);
        AddMenuItem("EndMacro", "EndMacro", &CommandHandler::EndMacro);
        AddMenuItem("ExecuteMacro", "ExecuteMacro Macro", &CommandHandler::ExecuteMacro);
        AddMenuItem(InsertParagraphCommand::name, "InsertParagraph end aaa", &CommandHandler::InsertParagraph);
        AddMenuItem("List", "Show document", &CommandHandler::List);
        AddMenuItem(SetTitleCommand::name, "Set title", &CommandHandler::SetTitle);
        AddMenuItem(ReplaceTextCommand::name, "Replace text", &CommandHandler::ReplaceText);
        AddMenuItem(DeleteItemCommand::name, "Delete item", &CommandHandler::DeleteItem);
        AddMenuItem("Undo", "Undo command", &CommandHandler::Undo);
        AddMenuItem("Redo", "Redo undone command", &CommandHandler::Redo);
        AddMenuItem("Save", "Save save.html", &CommandHandler::Save);
        AddMenuItem(InsertImageCommand::name, "InsertImage end 100 200 C:\\Volgatech\\3course\\OOD-labs\\lab5\\1.png", &CommandHandler::InsertImage);
        AddMenuItem(ResizeImageCommand::name, "ResizeImage 0 400 500", &CommandHandler::ResizeImage);
    }

private:
    Menu & m_menu;
    IDocument & m_document;
    bool m_isRecordMacro = false;
    std::vector<MacroCommand> m_macros;
    MacroCommand m_currentMacro = MacroCommand("");

    typedef void (CommandHandler::*MenuHandler)(std::istream & in);
    void AddMenuItem(const std::string & shortcut, const std::string & description, MenuHandler handler)
    {
        m_menu.AddItem(shortcut, description, bind(handler, this, std::placeholders::_1));
    }

    void BeginMacro(std::istream &in)
    {
        std::string nameMacro;

        in >> nameMacro;

        if (m_isRecordMacro) {
            throw std::invalid_argument("Already recording a macro.");
        }

        m_currentMacro = MacroCommand(nameMacro);
        std::cout << "Recording a new macro " << nameMacro << "..." << std::endl;
        m_isRecordMacro = true;
    }

    void EndMacro(std::istream &)
    {
        if (!m_isRecordMacro) {
            throw std::invalid_argument("No macro is currently being recorded.");
        }

        m_macros.push_back(std::move(m_currentMacro));
        std::cout << "Macro " << m_currentMacro.GetName() << " saved.\n";
        m_isRecordMacro = false;
    }

    void ExecuteMacro(std::istream &in)
    {
        std::string macroName;
        in >> macroName;

        auto it = std::find_if(m_macros.begin(), m_macros.end(),
                               [&macroName](const MacroCommand& macro) { return macro.GetName() == macroName; });

        if (it != m_macros.end()) {
            it->Execute();
            std::cout << "Executed macro: " << macroName << "\n";
        } else {
            throw std::invalid_argument("Macro not found.");
        }
    }

    void RecordCommand(std::function<void()> command) {
        if (m_isRecordMacro)
        {
            m_currentMacro.AddCommand(command);
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

        if (m_isRecordMacro)
        {
            RecordCommand([this, text, position]() {
                m_document.InsertParagraph(text, position);
                std::cout << "Inserted Paragraph.\n";
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

    void Undo(std::istream &)
    {
        if (m_document.CanUndo())
        {
            m_document.Undo();
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
            m_document.Redo();
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

        m_document.Save(path);
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

        m_document.InsertImage(path, width, height, position);
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

        m_document.ResizeImage(width, height, position);
    }
};

#endif //LAB5_COMMANDHANDLER_H
