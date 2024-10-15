#include "Document.h"

std::shared_ptr<IParagraph> Document::InsertParagraph(const std::string &text, std::optional<size_t> position)
{
    m_history.AddAndExecuteCommand(std::make_unique<InsertParagraphCommand>(m_documentItems, text, position));
    return nullptr;
}

std::shared_ptr<IImage>
Document::InsertImage(const std::string &path, int width, int height, std::optional<size_t> position)
{
    return nullptr;
}

size_t Document::GetItemsCount() const
{
    return m_documentItems.size();
}

ConstDocumentItem Document::GetItem(size_t index) const
{
    return m_documentItems.at(index);
}

DocumentItem Document::GetItem(size_t index)
{
    return m_documentItems.at(index);
}

void Document::DeleteItem(size_t index)
{

}

std::string Document::GetTitle() const
{
    return std::string();
}

void Document::SetTitle(const std::string &title)
{

}

bool Document::CanUndo() const
{
    return m_history.CanUndo();
}

void Document::Undo()
{
    m_history.Undo();
}

bool Document::CanRedo() const
{
    return m_history.CanRedo();
}

void Document::Redo()
{
    m_history.Redo();
}

void Document::Save(const std::string &path) const
{

}