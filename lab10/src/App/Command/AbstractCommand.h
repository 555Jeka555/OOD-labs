#ifndef LAB10_ABSTRACTCOMMAND_H
#define LAB10_ABSTRACTCOMMAND_H

#pragma once
#include "ICommand.h"

class AbstractCommand : public ICommand
{
public:
    void Execute() final
    {
        if (!m_executed)
        {
            DoExecute();
            m_executed = true;
        }
    }

    void Unexecute() final
    {
        if (m_executed)
        {
            DoUnexecute();
            m_executed = false;
        }
    }

protected:
    virtual void DoExecute() = 0;
    virtual void DoUnexecute() = 0;

private:
    bool m_executed = false;
};

#endif //LAB10_ABSTRACTCOMMAND_H
