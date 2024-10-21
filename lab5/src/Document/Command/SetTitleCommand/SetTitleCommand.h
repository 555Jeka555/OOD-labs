#ifndef LAB5_SETTITLECOMMAND_H
#define LAB5_SETTITLECOMMAND_H

#include <iostream>
#include <utility>
#include "../AbstractCommand/AbstractCommand.h"

class SetTitleCommand : public AbstractCommand
{
public:
    static constexpr std::string name = "SetTitle";

    SetTitleCommand(std::string & title, const std::string& newTitle) : m_title(title), m_newTitle(newTitle) {}

protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::string & m_title;
    std::string m_newTitle;
};


#endif //LAB5_SETTITLECOMMAND_H
