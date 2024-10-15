#ifndef LAB5_DOCUMENT_H
#define LAB5_DOCUMENT_H

#include "../IDocument.h"

class Document : public IDocument
{
public:
    std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
                                                        std::optional<size_t> position = std::nullopt) override;

    std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,
                                                std::optional<size_t> position = std::nullopt) override;
    
    [[nodiscard]] size_t GetItemsCount()const override;
    
    [[nodiscard]] ConstDocumentItem GetItem(size_t index)const override;
    
    DocumentItem GetItem(size_t index) override;
    
    void DeleteItem(size_t index) override;
    
    [[nodiscard]] std::string GetTitle()const override;
    
    void SetTitle(const std::string & title) override;
    
    [[nodiscard]] bool CanUndo()const override;
    
    void Undo() override;
    
    [[nodiscard]] bool CanRedo()const override;
    
    void Redo() override;
    
    void Save(const std::string& path)const override;
};


#endif //LAB5_DOCUMENT_H
