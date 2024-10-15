#ifndef LAB5_DOCUMENTITEM_H
#define LAB5_DOCUMENTITEM_H

#include <utility>
#include "ConstDocumentItem.h"
#include "Image/IImage.h"
#include "Paragraph/IParagraph.h"

class DocumentItem : public ConstDocumentItem
{
public:
    explicit DocumentItem (std::shared_ptr<IImage> image) : ConstDocumentItem(image), m_image(std::move(image)) {}

    explicit DocumentItem (std::shared_ptr<IParagraph> paragraph) : ConstDocumentItem(paragraph), m_paragraph(std::move(paragraph)) {}

    // Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
    std::shared_ptr<IImage> GetImage()
    {
        return m_image;
    }
    // Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
    std::shared_ptr<IParagraph> GetParagraph()
    {
        return m_paragraph;
    }

private:
    std::shared_ptr<IImage> m_image;
    std::shared_ptr<IParagraph> m_paragraph;
};

#endif //LAB5_DOCUMENTITEM_H
