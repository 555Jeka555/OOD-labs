#ifndef LAB5_PARAGRAPH_H
#define LAB5_PARAGRAPH_H

#include "IParagraph.h"

class Paragraph : public IParagraph
{
public:
    explicit Paragraph (std::string & text) : m_text(std::move(text)) {}

    [[nodiscard]] std::string GetText() const override
    {
        return m_text;
    }

    void SetText(const std::string& text) override
    {
        m_text = text;
    }

private:
    std::string m_text;
};


#endif //LAB5_PARAGRAPH_H
