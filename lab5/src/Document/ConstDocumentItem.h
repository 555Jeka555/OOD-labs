#ifndef LAB5_CONSTDOCUMENTITEM_H
#define LAB5_CONSTDOCUMENTITEM_H

#include <iostream>
#include <memory>
#include "../IImage.h"
#include "../IParagraph.h"

class ConstDocumentItem
{
public:
    // Возвращает указатель на константное изображение, либо nullptr,
// если элемент не является изображением
    std::shared_ptr<IImage> GetImage()const;
    // Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
    std::shared_ptr<IParagraph> GetParagraph()const;
    virtual ~ConstDocumentItem() = default;
};

#endif //LAB5_CONSTDOCUMENTITEM_H
