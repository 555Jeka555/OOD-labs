#include <gtest/gtest.h>
#include "../src/Document/Command/InsertParagraphCommand/InsertParagraphCommand.h"
#include "../src/Document/Command/ReplaceTextCommand/ReplaceTextCommand.h"
#include "../src/Document/Command/DeleteItemCommand/DeleteItemCommand.h"
#include "../src/Document/Command/SetTitleCommand/SetTitleCommand.h"
#include "../src/Document/Command/SaveCommand/SaveCommand.h"

class InsertParagraphCommandTestable : public InsertParagraphCommand {
public:
    InsertParagraphCommandTestable(std::vector<DocumentItem>& documentItems,
                                   std::string text,
                                   std::optional<size_t> position)
            : InsertParagraphCommand(documentItems, std::move(text), position) {}

    void TestDoExecute() {
        DoExecute();
    }

    void TestDoUnexecute() {
        DoUnexecute();
    }
};

class ReplaceTextCommandTestable : public ReplaceTextCommand {
public:
    ReplaceTextCommandTestable(std::vector<DocumentItem>& documentItems,
                               std::string newText,
                               std::optional<size_t> position)
            : ReplaceTextCommand(documentItems, std::move(newText), position) {}

    void TestDoExecute() {
        DoExecute();
    }

    void TestDoUnexecute() {
        DoUnexecute();
    }
};

class DeleteItemCommandTestable : public DeleteItemCommand {
public:
    DeleteItemCommandTestable(std::vector<DocumentItem>& documentItems, size_t position)
            : DeleteItemCommand(documentItems, position) {}

    // Public methods for calling protected methods
    void TestDoExecute() {
        DoExecute();
    }

    void TestDoUnexecute() {
        DoUnexecute();
    }
};

class SetTitleCommandTestable : public SetTitleCommand {
public:
    SetTitleCommandTestable(std::string& title, std::string newTitle)
            : SetTitleCommand(title, std::move(newTitle)) {}

    // Public methods to call the protected methods
    void TestDoExecute() {
        DoExecute();
    }

    void TestDoUnexecute() {
        DoUnexecute();
    }
};

class SaveCommandTestable : public SaveCommand {
public:
    SaveCommandTestable(const std::vector<DocumentItem>& documentItems, std::string path, std::string title)
            : SaveCommand(documentItems, std::move(path), std::move(title)) {}

    void TestDoExecute() {
        DoExecute();
    }

    void TestDoUnexecute() {
        DoUnexecute();
    }
};

TEST(InsertParagraphCommandTest, InsertAtEndSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string text = "New paragraph text";

    InsertParagraphCommandTestable command(documentItems, text, std::nullopt);

    command.TestDoExecute();

    ASSERT_EQ(documentItems.size(), 1);

    auto paragraph = std::dynamic_pointer_cast<Paragraph>(documentItems[0].GetParagraph());
    ASSERT_NE(paragraph, nullptr);
    EXPECT_EQ(paragraph->GetText(), text);

    command.TestDoUnexecute();

    EXPECT_TRUE(documentItems.empty());
}

TEST(InsertParagraphCommandTest, InsertAtPositionSuccess) {
    std::string text = "Existing paragraph";
    auto paragraph = std::make_shared<Paragraph>(text);
    DocumentItem documentItem(paragraph);
    std::vector<DocumentItem> documentItems = {documentItem};

    std::string textInserted = "Inserted paragraph";
    size_t position = 0;

    InsertParagraphCommandTestable command(documentItems, textInserted, position);

    command.TestDoExecute();

    ASSERT_EQ(documentItems.size(), 2);

    auto paragraph1 = std::dynamic_pointer_cast<Paragraph>(documentItems[position].GetParagraph());
    ASSERT_NE(paragraph1, nullptr);
    EXPECT_EQ(paragraph1->GetText(), textInserted);

    command.TestDoUnexecute();

    ASSERT_EQ(documentItems.size(), 1);
    EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Existing paragraph");
}

TEST(InsertParagraphCommandTest, InsertAtInvalidPositionError) {
    std::vector<DocumentItem> documentItems;
    std::string text = "Text for invalid position";
    size_t invalidPosition = 10;

    InsertParagraphCommandTestable command(documentItems, text, invalidPosition);

    EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
    EXPECT_TRUE(documentItems.empty());
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextAtPositionSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string oldText = "Original text";
    documentItems.emplace_back(std::make_shared<Paragraph>(oldText));

    std::string newText = "Replaced text";
    size_t position = 0;

    ReplaceTextCommandTestable command(documentItems, newText, position);

    command.TestDoExecute();

    auto paragraph = std::dynamic_pointer_cast<Paragraph>(documentItems[position].GetParagraph());
    ASSERT_NE(paragraph, nullptr);
    EXPECT_EQ(paragraph->GetText(), newText);

    command.TestDoUnexecute();

    EXPECT_EQ(paragraph->GetText(), "Original text");
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextWithInvalidPositionError) {
    std::vector<DocumentItem> documentItems;
    std::string newText = "Text for invalid position";
    size_t invalidPosition = 10;

    ReplaceTextCommandTestable command(documentItems, newText, invalidPosition);

    EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextWithoutPositionError) {
    std::vector<DocumentItem> documentItems;
    std::string newText = "Text for no position";

    ReplaceTextCommandTestable command(documentItems, newText, std::nullopt);

    EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ReplaceTextCommandTest, DoUnexecuteRestoreOriginalTextSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string oldText = "Initial text";
    documentItems.emplace_back(std::make_shared<Paragraph>(oldText));

    std::string newText = "New text";
    size_t position = 0;

    ReplaceTextCommandTestable command(documentItems, newText, position);

    command.TestDoExecute();

    auto paragraph = std::dynamic_pointer_cast<Paragraph>(documentItems[position].GetParagraph());
    ASSERT_NE(paragraph, nullptr);
    EXPECT_EQ(paragraph->GetText(), newText);

    command.TestDoUnexecute();

    EXPECT_EQ(paragraph->GetText(), "Initial text");
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemAtSpecifiedPositionSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string text1 = "Paragraph 1";
    std::string text2 = "Paragraph 2";
    documentItems.emplace_back(std::make_shared<Paragraph>(text1));
    documentItems.emplace_back(std::make_shared<Paragraph>(text2));

    size_t position = 1;
    DeleteItemCommandTestable command(documentItems, position);

    command.TestDoExecute();

    ASSERT_EQ(documentItems.size(), 1);
    EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Paragraph 1");

    command.TestDoUnexecute();

    ASSERT_EQ(documentItems.size(), 2);
    EXPECT_EQ(documentItems[1].GetParagraph()->GetText(), "Paragraph 2");
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemWithInvalidPositionError) {
    std::vector<DocumentItem> documentItems;
    std::string text = "Paragraph 1";
    documentItems.emplace_back(std::make_shared<Paragraph>(text));

    size_t invalidPosition = 5;
    DeleteItemCommandTestable command(documentItems, invalidPosition);

    EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(DeleteItemCommandTest, DoExecuteDeleteOnlyItemSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string text = "Only paragraph";
    documentItems.emplace_back(std::make_shared<Paragraph>(text));

    size_t position = 0;
    DeleteItemCommandTestable command(documentItems, position);

    command.TestDoExecute();

    EXPECT_TRUE(documentItems.empty());

    command.TestDoUnexecute();

    ASSERT_EQ(documentItems.size(), 1);
    EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Only paragraph");
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemAtPositionZeroSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string text1 = "Paragraph 1";
    std::string text2 = "Paragraph 2";
    std::string text3 = "Paragraph 3";
    documentItems.emplace_back(std::make_shared<Paragraph>(text1));
    documentItems.emplace_back(std::make_shared<Paragraph>(text2));
    documentItems.emplace_back(std::make_shared<Paragraph>(text3));

    size_t position = 0;
    DeleteItemCommandTestable command(documentItems, position);

    command.TestDoExecute();

    ASSERT_EQ(documentItems.size(), 2);
    EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Paragraph 2");

    command.TestDoUnexecute();

    ASSERT_EQ(documentItems.size(), 3);
    EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Paragraph 1");
}

TEST(DeleteItemCommandTest, DoUnexecuteOnEmptyListError) {
    std::vector<DocumentItem> documentItems;

    size_t position = 0;
    DeleteItemCommandTestable command(documentItems, position);

    EXPECT_NO_THROW(command.TestDoUnexecute());

    EXPECT_TRUE(documentItems.empty());
}

TEST(SetTitleCommandTest, DoExecuteSetsNewTitleSuccess) {
    std::string title = "Original Title";
    std::string newTitle = "New Title";

    SetTitleCommandTestable command(title, newTitle);

    command.TestDoExecute();

    EXPECT_EQ(title, "New Title");

    command.TestDoUnexecute();

    EXPECT_EQ(title, "Original Title");
}

TEST(SetTitleCommandTest, DoUnexecuteRevertsToOldTitleSuccess) {
    std::string title = "Initial Title";
    std::string newTitle = "Updated Title";

    SetTitleCommandTestable command(title, newTitle);

    command.TestDoExecute();

    EXPECT_EQ(title, "Updated Title");

    command.TestDoUnexecute();

    EXPECT_EQ(title, "Initial Title");
}

TEST(SetTitleCommandTest, RepeatedExecuteAndUnexecuteSuccess) {
    std::string title = "Start Title";
    std::string newTitle = "Changed Title";

    SetTitleCommandTestable command(title, newTitle);

    command.TestDoExecute();
    EXPECT_EQ(title, "Changed Title");

    command.TestDoUnexecute();
    EXPECT_EQ(title, "Start Title");

    command.TestDoExecute();
    EXPECT_EQ(title, "Changed Title");

    command.TestDoUnexecute();
    EXPECT_EQ(title, "Start Title");
}

TEST(SetTitleCommandTest, DoExecuteWithSameTitleSuccess) {
    std::string title = "Same Title";

    SetTitleCommandTestable command(title, title);

    command.TestDoExecute();

    EXPECT_EQ(title, "Same Title");

    command.TestDoUnexecute();

    EXPECT_EQ(title, "Same Title");
}

TEST(SaveCommandTest, DoExecuteCreatesHtmlFile) {
    std::vector<DocumentItem> documentItems;
    std::string title = "Test Document";
    std::string filePath = "test_output.html";

    documentItems.emplace_back(std::make_shared<Paragraph>("Paragraph 1"));
    documentItems.emplace_back(std::make_shared<Paragraph>("Paragraph 2"));

    SaveCommandTestable command(documentItems, filePath, title);

    command.TestDoExecute();

    std::ifstream inFile(filePath);
    ASSERT_TRUE(inFile.is_open());

    std::string line;
    std::getline(inFile, line);
    EXPECT_EQ(line, "<!DOCTYPE html>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "<html>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "<head>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "<title>Test Document</title>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "</head>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "<body>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "<p>Paragraph 1</p>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "<p>Paragraph 2</p>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "</body>");

    std::getline(inFile, line);
    EXPECT_EQ(line, "</html>");

    inFile.close();

    std::filesystem::remove(filePath);
}

TEST(SaveCommandTest, DoExecuteThrowsExceptionWhenFileCannotBeOpenedError) {
    std::string invalidPath = "/invalid_path/test_output.html";
    std::vector<DocumentItem> documentItems;

    SaveCommandTestable command(documentItems, invalidPath, "Test Document");

    EXPECT_THROW(command.TestDoExecute(), std::runtime_error);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}