#include "InsertParagraphCommand.h"

void InsertParagraphCommand::DoExecute()
{
    auto paragraph = std::make_shared<Paragraph>(m_text);
    DocumentItem documentItem(paragraph);

    if (!m_position.has_value())
    {
        m_documentItems.push_back(documentItem);
    }
}

void InsertParagraphCommand::DoUnexecute()
{
    if (m_documentItems.empty())
    {
        return;
    }

    if (!m_position.has_value())
    {
        m_documentItems.pop_back();
    }
}
