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
    static constexpr std::string name = "DeleteItem";

    DeleteItemCommand(std::vector<DocumentItem> & documentItems, size_t position, DocumentItem & oldDocumentItem)
        : m_documentItems(documentItems), m_position(position), m_oldDocumentItem(oldDocumentItem) {}

protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::vector<DocumentItem> & m_documentItems;
    size_t m_position;
    DocumentItem & m_oldDocumentItem;
};


#endif //LAB5_DELETEITEMCOMMAND_H
