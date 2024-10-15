#include "DeleteItemCommand.h"

void DeleteItemCommand::DoExecute()
{
    if (m_position >= m_documentItems.size())
    {
        throw std::invalid_argument("Out of range by position");
    }

    m_documentItems.erase(m_documentItems.begin() + static_cast<std::vector<DocumentItem>::iterator::difference_type>(m_position));
}

void DeleteItemCommand::DoUnexecute()
{
    m_documentItems.insert(
            m_documentItems.begin() + static_cast<std::vector<DocumentItem>::iterator::difference_type>(m_position),
            *m_oldDocumentItem);
}
