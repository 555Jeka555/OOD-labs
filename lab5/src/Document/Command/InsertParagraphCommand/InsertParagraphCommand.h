#ifndef LAB5_INSERTPARAGRAPHCOMMAND_H
#define LAB5_INSERTPARAGRAPHCOMMAND_H

#include <iostream>
#include <utility>
#include <vector>
#include <optional>
#include "../AbstractCommand/AbstractCommand.h"
#include "../../DocumentItem.h"
#include "../../Paragraph/Paragraph.h"

class InsertParagraphCommand : public AbstractCommand
{
public:
    static constexpr std::string name = "InsertParagraph";

    InsertParagraphCommand(std::vector<DocumentItem> & documentItems,
                           const std::string& text,
                           std::optional<size_t> position)
                           : m_documentItems(documentItems), m_text(text), m_position(position) {};
protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::vector<DocumentItem> & m_documentItems;
    std::string m_text;
    std::optional<size_t> m_position;
};


#endif //LAB5_INSERTPARAGRAPHCOMMAND_H
