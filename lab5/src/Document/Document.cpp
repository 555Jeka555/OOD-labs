#include "Document.h"

std::shared_ptr<IParagraph> Document::InsertParagraph(const std::string &text, std::optional<size_t> position)
{
    return nullptr;
}

std::shared_ptr<IImage>
Document::InsertImage(const std::string &path, int width, int height, std::optional<size_t> position)
{
    return nullptr;
}

size_t Document::GetItemsCount() const
{
    return 0;
}

ConstDocumentItem Document::GetItem(size_t index) const
{
    return ConstDocumentItem();
}

DocumentItem Document::GetItem(size_t index)
{
    return DocumentItem();
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
    return false;
}

void Document::Undo()
{

}

bool Document::CanRedo() const
{
    return false;
}

void Document::Redo()
{

}

void Document::Save(const std::string &path) const
{

}
