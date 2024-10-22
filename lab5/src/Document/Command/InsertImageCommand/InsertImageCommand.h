#ifndef LAB5_INSERTIMAGECOMMAND_H
#define LAB5_INSERTIMAGECOMMAND_H

#include <iostream>
#include <vector>
#include <optional>
#include <filesystem>
#include <fstream>
#include "../AbstractCommand/AbstractCommand.h"
#include "../../DocumentItem.h"
#include "../../Image/Image.h"

class InsertImageCommand : public AbstractCommand
{
public:
    static constexpr std::string name = "InsertImage";

    InsertImageCommand(
            std::vector<DocumentItem>& documentItems,
            const std::string& path,
            int width,
            int height,
            std::optional<size_t> position
            ) : m_documentItems(documentItems), m_path(path), m_width(width), m_height(height), m_position(position)
            {}

    ~InsertImageCommand() override
    {
        InsertImageCommand::DeleteFileIfExists();
    }
protected:
    void DoExecute() override;
    void DoUnexecute() override;

private:
    std::string TMP_DIR_PATH = "tmp";
    std::vector<DocumentItem>& m_documentItems;
    std::string m_path;
    std::string m_tmpPath;
    int m_width;
    int m_height;
    std::optional<size_t> m_position;

    void CopyImage();

    void DeleteFileIfExists();
};


#endif //LAB5_INSERTIMAGECOMMAND_H
