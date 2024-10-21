#ifndef LAB5_RESIZEIMAGECOMMAND_H
#define LAB5_RESIZEIMAGECOMMAND_H

#include <iostream>
#include <vector>
#include <optional>
#include <filesystem>
#include <fstream>
#include "../AbstractCommand/AbstractCommand.h"
#include "../../DocumentItem.h"
#include "../../Image/Image.h"

class ResizeImageCommand : public AbstractCommand
{
public:
    static constexpr std::string name = "ResizeImage";

    ResizeImageCommand(std::vector<DocumentItem> & documentItems,
                       int newWidth, int newHeight,
                       std::optional<size_t> position)
            : m_documentItems(documentItems), m_newHeight(newHeight), m_newWidth(newWidth), m_position(position) {};

protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::vector<DocumentItem> & m_documentItems;
    int m_height = 0;
    int m_width = 0;
    int m_newHeight;
    int m_newWidth;
    std::optional<size_t> m_position;
};


#endif //LAB5_RESIZEIMAGECOMMAND_H
