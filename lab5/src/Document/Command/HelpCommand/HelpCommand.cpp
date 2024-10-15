#include "HelpCommand.h"

void HelpCommand::DoExecute()
{
    std::cout << "InsertParagraph <позиция>|end <текст параграфа>\n"
        << "InsertImage <позиция>|end <ширина> <высота> <путь к файлу изображения>\n"
        << "SetTitle <заголовок документа>\n"
        << "List\n"
        << "ReplaceText <позиция> <текст параграфа>\n"
        << "ResizeImage <позиция> <ширина> <высота>\n"
        << "DeleteItem <позиция>\n"
        << "Help\n"
        << "Undo\n"
        << "Redo\n"
        << "Save <путь>\n";
}

void HelpCommand::DoUnexecute()
{

}
