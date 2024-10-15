#ifndef LAB5_HELPCOMMAND_H
#define LAB5_HELPCOMMAND_H

#include <iostream>
#include "../AbstractCommand/AbstractCommand.h"

class HelpCommand : public AbstractCommand
{
public:
    static constexpr std::string name = "Help";
protected:
    void DoExecute() override;
    void DoUnexecute() override;
};


#endif //LAB5_HELPCOMMAND_H
