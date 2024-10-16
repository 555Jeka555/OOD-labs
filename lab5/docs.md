```mermaid
classDiagram
    ICommand <|.. AbstractCommand
    AbstractCommand <|-- InsertParagraphCommand
    AbstractCommand <|-- SetTitleCommand
    AbstractCommand <|-- DeleteCommand
    AbstractCommand <|-- SaveCommand
    AbstractCommand <|-- ReplaceTextCommand

    IParagraph <|.. Paragraph
    IImage <|.. Image

    History *-- ICommand

    ConstDocumentItem <|-- DocumentItem

    IDocument <|.. Document
    ConstDocumentItem *-- IImage
    ConstDocumentItem *-- IParagraph
    DocumentItem *-- IImage
    DocumentItem *-- IParagraph
    Document *-- History
    Document *-- InsertParagraphCommand
    Document *-- SetTitleCommand
    Document *-- DeleteCommand
    Document *-- SaveCommand
    Document *-- ReplaceTextCommand

    Paragraph <.. InsertParagraphCommand : "Create"
    Paragraph <.. ReplaceTextCommand : "Use"
    InsertParagraphCommand o-- DocumentItem
    DeleteCommand o-- DocumentItem
    DeleteCommand *-- DocumentItem
    SaveCommand o-- DocumentItem
    ReplaceTextCommand o-- DocumentItem
    
    Menu *-- Item
    Menu o-- Document

    CommandHandler o-- Document
    CommandHandler o-- Menu
    
    class CommandHandler {
        - m_menu Menu
        - m_document Document
        - AddMenuItem(shortcut string, description string)
        - List(in istream)
        - InsertParagraph(in istream)
        - SetTitle(in istream)
        - ReplaceText(in istream)
        - DeleteItem(in istream)
        - Undo(in istream)
        - Redo(in istream)
        - Save(in istream)
    }

    class IDocument {
        + InsertParagraph(text string, position size_t)*
        + ReplaceText(text string, position size_t)*
        + InsertImage(path string, width int, height int, position size_t)* IImage
        + ResizeImage(width int, height int, position size_t)*
        + GetItemsCount()* size_t;
        + GetItem(index size_t)* ConstDocumentItem
        + GetItem(index size_t)* DocumentItem
        + DeleteItem(index size_t)*
        + GetTitle()* string
        + SetTitle(title string)*
        + CanUndo()* bool
        + Undo()*
        + CanRedo()* bool
        + Redo()*
        + Save(path string)*
    }

    class Document {
        + InsertParagraph(text string, position size_t)
        + ReplaceText(text string, position size_t)
        + InsertImage(path string, width int, height int, position size_t) IImage
        + ResizeImage(width int, height int, position size_t)
        + GetItemsCount() size_t;
        + GetItem(index size_t) ConstDocumentItem
        + GetItem(index size_t) DocumentItem
        + DeleteItem(index size_t)
        + GetTitle() string
        + SetTitle(title string)
        + CanUndo() bool
        + Undo()
        + CanRedo() bool
        + Redo()
        + Save(path string)
        - m_history History
        - m_title string
        - m_items map(DocumentItem)
    }

    class IParagraph {
        + GetText()* string
        + SetText(text string)*
    }

    class Paragraph {
        + GetText() string
        + SetText(text string)
    }

    class IImage {
        + GetPath()* string
        + GetWidth()* int
        + GetHeight()* int
        + Resize(width int, height int)*
    }

    class Image {
        + GetPath() string
        + GetWidth() int
        + GetHeight() int
        + Resize(width int, height int)
    }

    class ConstDocumentItem {
        + GetImage() IImage
        + GetIParahraph() IParagraph
    }

    class DocumentItem {
        + GetImage() IImage
        + GetIParahraph() IParagraph
    }

    class ICommand {
        + Execute()*
        + Unexecute()*
    }

    class AbstractCommand {
        + Execute()
        + Unexecute()
        # DoExecute()*
        # DoUnexecute()*
        - m_executed bool
    }

    class History {
        + CanUndo() bool
        + Undo()
        + CanRedo() bool
        + Redo()
        + AddAndExecuteCommand(command ICommand)
        - m_commands deque(ICommand)
        - m_nextCommandIndex size_t
    }

    class Menu {
        + AddItem(shortcut string, description string, command function void(&args istream))
        + Run()
        + ShowInstructions()
        + Exit()
        - ExecuteCommand(command string)
        - m_items vector(Item) 
        - m_exit bool
    }

    class Item {
        + shortcut string
        + description string
        + command ICommand
    }

    class InsertParagraphCommand {
        # DoExecute()
        # DoUnexecute()
        - m_document vector(DocumentItem)
        - m_position size_t
        - m_text string
    }

    class SetTitleCommand {
        # DoExecute()
        # DoUnexecute()
        - m_newTitle string
        - m_title string
    }

    class DeleteCommand {
        # DoExecute()
        # DoUnexecute()
        - m_document vector(DocumentItem)
        - m_position size_t
        - m_oldDocumentItem DocumentItem
    }

    class SaveCommand {
        # DoExecute()
        # DoUnexecute()
        - m_document vector(DocumentItem)
        - m_path string
        - m_title string
    }

    class ReplaceTextCommand {
        # DoExecute()
        # DoUnexecute()
        - m_document vector(DocumentItem)
        - m_position size_t
        - m_text string
        - m_newText string
    }
```