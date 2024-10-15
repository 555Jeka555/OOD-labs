#include "SaveCommand.h"

std::string SaveCommand::HtmlEncode(const std::string &text) {
    std::string encoded;
    for (char c : text) {
        switch (c) {
            case '<': encoded += "&lt;"; break;
            case '>': encoded += "&gt;"; break;
            case '"': encoded += "&quot;"; break;
            case '\'': encoded += "&apos;"; break;
            case '&': encoded += "&amp;"; break;
            default: encoded += c; break;
        }
    }
    return encoded;
}

void SaveCommand::DoExecute()
{
    std::ofstream outFile(m_path);
    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file for writing");
    }

    outFile << "<!DOCTYPE html>\n<html>\n<head>\n";
    outFile << "<title>" << HtmlEncode(m_title) << "</title>\n";
    outFile << "</head>\n<body>\n";

    for (const ConstDocumentItem &item : m_documentItems) {
        auto paragraph = item.GetParagraph();
        if (paragraph != nullptr) {
            outFile << "<p>" << HtmlEncode(paragraph->GetText()) << "</p>\n";
        }
    }

    outFile << "</body>\n</html>";

    outFile.close();
}

void SaveCommand::DoUnexecute()
{

}


