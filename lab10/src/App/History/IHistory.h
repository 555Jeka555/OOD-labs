#ifndef LAB10_IHISTORY_H
#define LAB10_IHISTORY_H

#pragma once

class IHistory
{
public:
    virtual bool CanUndo() const = 0;
    virtual bool CanRedo() const = 0;

    virtual void Undo() = 0;
    virtual void Redo() = 0;
};

#endif //LAB10_IHISTORY_H
