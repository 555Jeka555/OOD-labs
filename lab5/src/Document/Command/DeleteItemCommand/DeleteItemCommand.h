#ifndef LAB5_DELETEITEMCOMMAND_H
#define LAB5_DELETEITEMCOMMAND_H

#include <iostream>
#include <optional>
#include <vector>
#include "../AbstractCommand/AbstractCommand.h"
#include "../../DocumentItem.h"

class DeleteItemCommand : public AbstractCommand
{
public:
    static constexpr const char* name = "DeleteItem"; // Используйте const char*

    DeleteItemCommand(std::vector<DocumentItem>& documentItems, size_t position)
            : m_documentItems(documentItems), m_position(position)
    {
        m_oldDocumentItem = std::make_unique<DocumentItem>(m_documentItems.at(m_position));
    }

protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::vector<DocumentItem>& m_documentItems;
    size_t m_position;
    std::unique_ptr<DocumentItem> m_oldDocumentItem;
};

#endif //LAB5_DELETEITEMCOMMAND_H