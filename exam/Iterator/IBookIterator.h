#ifndef EXAM_IBOOKITERATOR_H
#define EXAM_IBOOKITERATOR_H

#include "Book.h"

class IBookIterator
{
public:
    virtual ~IBookIterator() = default;

    virtual const Book& GetBook() const = 0;
    virtual bool HasBook() const = 0;
    virtual void Next() = 0;
};


#endif //EXAM_IBOOKITERATOR_H
