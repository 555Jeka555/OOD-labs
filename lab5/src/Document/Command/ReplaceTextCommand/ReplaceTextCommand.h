#ifndef LAB5_REPLACETEXTCOMMAND_H
#define LAB5_REPLACETEXTCOMMAND_H

#include <iostream>
#include <utility>
#include <vector>
#include <optional>
#include "../AbstractCommand/AbstractCommand.h"
#include "../../DocumentItem.h"
#include "../../Paragraph/Paragraph.h"

class ReplaceTextCommand : public AbstractCommand
{
public:
    static constexpr std::string name = "ReplaceText";

    ReplaceTextCommand(std::vector<DocumentItem> & documentItems,
            const std::string& newText,
            std::optional<size_t> position)
    : m_documentItems(documentItems), m_newText(newText), m_position(position) {};
protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::vector<DocumentItem> & m_documentItems;
    std::string m_text;
    std::string m_newText;
    std::optional<size_t> m_position;
};


#endif //LAB5_REPLACETEXTCOMMAND_H
