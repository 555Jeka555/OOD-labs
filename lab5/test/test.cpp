#include <gtest/gtest.h>
#include <sstream>
#include "../src/Document/Command/InsertParagraphCommand/InsertParagraphCommand.h"
#include "../src/Document/Command/ReplaceTextCommand/ReplaceTextCommand.h"
#include "../src/Document/Command/DeleteItemCommand/DeleteItemCommand.h"
#include "../src/Document/Command/SetTitleCommand/SetTitleCommand.h"
#include "../src/Document/Command/SaveCommand/SaveCommand.h"
#include "../src/Document/Command/InsertImageCommand/InsertImageCommand.h"
#include "../src/Document/Command/ResizeImageCommand/ResizeImageCommand.h"
#include "../src/Document/Command/MacroCommand/MacroCommand.h"
#include "../src/Document/IDocument.h"
#include "../src/Menu/Menu.h"
#include "../src/Document/Document/Document.h"

const std::string IMAGE_PATH = "test/1.png";

class InsertParagraphCommandTestable : public InsertParagraphCommand {
public:
    InsertParagraphCommandTestable(std::vector<DocumentItem>& documentItems,
                                   const std::string& text,
                                   std::optional<size_t> position)
            : InsertParagraphCommand(documentItems, text, position) {}

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
                               const std::string& newText,
                               std::optional<size_t> position)
            : ReplaceTextCommand(documentItems, newText, position) {}

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

    void TestDoExecute() {
        DoExecute();
    }

    void TestDoUnexecute() {
        DoUnexecute();
    }
};

class SetTitleCommandTestable : public SetTitleCommand {
public:
    SetTitleCommandTestable(std::string& title, const std::string& newTitle)
            : SetTitleCommand(title, newTitle) {}

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

class InsertImageCommandTestable : public InsertImageCommand {
public:
    InsertImageCommandTestable(
            std::vector<DocumentItem>& documentItems,
            const std::string& path,
            int width,
            int height,
            std::optional<size_t> position)
            : InsertImageCommand(documentItems, path, width, height, position) {}

    void TestDoExecute() {
        DoExecute();
    }

    void TestDoUnexecute() {
        DoUnexecute();
    }
};

class ResizeImageCommandTestable : public ResizeImageCommand {
public:
    ResizeImageCommandTestable(
            std::vector<DocumentItem>& documentItems,
            std::optional<size_t> position,
            int newWidth,
            int newHeight)
            : ResizeImageCommand(documentItems, newWidth, newHeight, position) {}

    void TestDoExecute() {
        DoExecute();
    }

    void TestDoUnexecute() {
        DoUnexecute();
    }
};

class MacroCommandTestable : public MacroCommand {
public:
    MacroCommandTestable(const std::string & name, const std::string & description)
            : MacroCommand(name, description) {}

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

TEST(SaveCommandTest, DoExecuteCreatesHtmlFileWithImagesSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string title = "Test Document";
    std::string filePath = "test_output_with_images.html";

    documentItems.emplace_back(std::make_shared<Paragraph>("Paragraph 1"));
    documentItems.emplace_back(std::make_shared<Paragraph>("Paragraph 2"));

    std::string imagePath = IMAGE_PATH;
    documentItems.emplace_back(std::make_shared<Image>(imagePath, 100, 200));

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
    EXPECT_EQ(line, "<img src=\"images/1.png\" alt=\"1.png\" width=\"100\" height=\"200\" />");

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

TEST(InsertImageCommandTests, ExecuteInsertsImageAtEndSuccess)
{
    std::vector<DocumentItem> documentItems;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommandTestable command(documentItems, imagePath, width, height, std::nullopt);

    EXPECT_NO_THROW(command.TestDoExecute());

    ASSERT_EQ(documentItems.size(), 1);
    EXPECT_TRUE(std::filesystem::exists(imagePath));
}

TEST(InsertImageCommandTests, ExecuteInsertsImageAtPositionSuccess)
{
    std::vector<DocumentItem> documentItems;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommandTestable command(documentItems, imagePath, width, height, 0);

    EXPECT_NO_THROW(command.TestDoExecute());

    ASSERT_EQ(documentItems.size(), 1);
    EXPECT_TRUE(std::filesystem::exists(imagePath));
}

TEST(InsertImageCommandTests, ExecuteThrowsOnInvalidPositionError) {
    std::vector<DocumentItem> documentItems;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommandTestable command(documentItems, imagePath, width, height, 2);

    EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(InsertImageCommandTests, UnexecuteRemovesLastInsertedSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommandTestable command(documentItems, imagePath, width, height, std::nullopt);

    command.TestDoExecute();
    ASSERT_EQ(documentItems.size(), 1);
    EXPECT_TRUE(std::filesystem::exists(imagePath));

    command.TestDoUnexecute();
    ASSERT_EQ(documentItems.size(), 0);
}

TEST(InsertImageCommandTests, UnexecuteRemovesInsertedAtPositionSuccess) {
    std::vector<DocumentItem> documentItems;
    std::string imagePath = IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommandTestable command(documentItems, imagePath, width, height, 0);

    command.TestDoExecute();
    ASSERT_EQ(documentItems.size(), 1);
    EXPECT_TRUE(std::filesystem::exists(imagePath));

    command.TestDoUnexecute();
    ASSERT_EQ(documentItems.size(), 0);
}

TEST(InsertImageCommandTests, ExecuteThrowsOnNonExistentImageError) {
    std::vector<DocumentItem> documentItems;
    std::string nonExistentImagePath = "1/" + IMAGE_PATH;
    int width = 100;
    int height = 200;

    InsertImageCommandTestable command(documentItems, nonExistentImagePath, width, height, std::nullopt);

    EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
    EXPECT_TRUE(!std::filesystem::exists(nonExistentImagePath));
}

TEST(ResizeImageCommandTests, ExecuteResizesImageSuccess) {
    std::vector<DocumentItem> documentItems;
    auto image = std::make_shared<Image>(IMAGE_PATH, 100, 200);
    documentItems.emplace_back(image);

    ResizeImageCommandTestable command(documentItems, 0, 150, 300);

    EXPECT_NO_THROW(command.TestDoExecute());

    ASSERT_EQ(image->GetHeight(), 300);
    ASSERT_EQ(image->GetWidth(), 150);
}

TEST(ResizeImageCommandTests, ExecuteThrowsOnInvalidPositionError) {
    std::vector<DocumentItem> documentItems;
    auto image = std::make_shared<Image>(IMAGE_PATH, 100, 200);
    documentItems.emplace_back(image);

    ResizeImageCommandTestable command(documentItems, 1, 300, 150);

    EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTests, ExecuteThrowsWhenNoImageAtPositionError) {
    std::vector<DocumentItem> documentItems;

    ResizeImageCommandTestable command(documentItems, 0, 150, 300);

    EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTests, UnexecuteResizesBackToOriginalSizeSuccess) {
    std::vector<DocumentItem> documentItems;
    auto image = std::make_shared<Image>(IMAGE_PATH, 100, 200);
    documentItems.emplace_back(image);

    ResizeImageCommandTestable command(documentItems, 0, 150, 300);

    command.TestDoExecute();
    ASSERT_EQ(image->GetWidth(), 150);
    ASSERT_EQ(image->GetHeight(), 300);

    command.TestDoUnexecute();

    ASSERT_EQ(image->GetWidth(), 100);
    ASSERT_EQ(image->GetHeight(), 200);
}

TEST(ResizeImageCommandTests, UnexecuteThrowsOnInvalidPositionError) {
    std::vector<DocumentItem> documentItems;
    auto image = std::make_shared<Image>(IMAGE_PATH, 100, 200);
    documentItems.emplace_back(image);

    ResizeImageCommandTestable command(documentItems, 1, 150, 300);

    EXPECT_THROW(command.TestDoUnexecute(), std::invalid_argument);
}

TEST(MacroCommandTests, ExecuteRunsAllCommandsInOrderSuccess)
{
    int counter = 0;

    MacroCommandTestable macro("Test Macro", "This is a test macro");

    macro.AddCommand([&counter]() { counter += 1; });
    macro.AddCommand([&counter]() { counter *= 2; });

    macro.TestDoExecute();

    ASSERT_EQ(counter, 2);
}

TEST(MenuTests, AddItemIncreasesItemCountSuccess)
{
    Menu menu;
    menu.AddItem("TestCommand", "This is a test command", [](std::istream&) {});

    ASSERT_EQ(menu.GetItemsCount(), 1);
}

TEST(MenuTests, ExecuteCommandCallsCorrectFunctionSuccess)
{
    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

    Menu menu;

    bool called = false;

    menu.AddItem("TestCommand", "This is a test command", [&called](std::istream&) {
        called = true;
    });

    std::istringstream input("\n");
    std::streambuf* originalCinBuffer = std::cin.rdbuf(input.rdbuf());
    menu.Run();
    std::cin.rdbuf(originalCinBuffer);
    menu.Exit();

    std::cout.rdbuf(originalCoutBuffer);
    EXPECT_EQ(output.str(), "Commands list:\n  TestCommand: This is a test command\n>");
}

TEST(DocumentTests, InsertParagraphIncreasesItemCountSuccess)
{
    Document document;
    size_t initialCount = document.GetItemsCount();
    document.InsertParagraph("Test paragraph");

    EXPECT_EQ(document.GetItemsCount(), initialCount + 1);
}

TEST(DocumentTests, ReplaceTextUpdatesCorrectlySuccess)
{
    Document document;
    document.InsertParagraph("Original text");
    document.ReplaceText("Updated text", 0);

    EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "Updated text");
}

TEST(DocumentTests, InsertImageIncreasesItemCountSuccess)
{
    Document document;
    size_t initialCount = document.GetItemsCount();
    document.InsertImage(IMAGE_PATH, 100, 200);

    EXPECT_EQ(document.GetItemsCount(), initialCount + 1);
}

TEST(DocumentTests, DeleteItemDecreasesItemCountSuccess)
{
    Document document;
    document.InsertParagraph("First paragraph");
    document.InsertParagraph("Second paragraph");

    size_t initialCount = document.GetItemsCount();
    document.DeleteItem(0);

    EXPECT_EQ(document.GetItemsCount(), initialCount - 1);
}

TEST(DocumentTests, GetTitleReturnsCorrectTitleSuccess)
{
    Document document;
    document.SetTitle("Test Title");

    EXPECT_EQ(document.GetTitle(), "Test Title");
}

TEST(DocumentTests, CanUndoReturnsTrueAfterActionSuccess)
{
    Document document;
    document.InsertParagraph("A paragraph");

    EXPECT_TRUE(document.CanUndo());
}

TEST(DocumentTests, UndoRevertsLastActionSuccess)
{
    Document document;
    document.InsertParagraph("A paragraph");
    size_t countAfterInsert = document.GetItemsCount();

    document.Undo();

    EXPECT_EQ(document.GetItemsCount(), countAfterInsert - 1);
}

TEST(DocumentTests, CanRedoReturnsTrueAfterUndoSuccess)
{
    Document document;
    document.InsertParagraph("A paragraph");
    document.Undo();

    EXPECT_TRUE(document.CanRedo());
}

TEST(DocumentTests, RedoRestoresLastActionSuccess)
{
    Document document;
    document.InsertParagraph("A paragraph");
    document.Undo();

    size_t countAfterUndo = document.GetItemsCount();

    document.Redo();

    EXPECT_EQ(document.GetItemsCount(), countAfterUndo + 1);
}

TEST(HistoryTests, InitialStateSucess)
{
    History history;
    EXPECT_FALSE(history.CanUndo());
    EXPECT_FALSE(history.CanRedo());
}

TEST(HistoryTests, AddCommandAndUndoSucess)
{
    History history;
    std::string title = "Original Title";
    std::string newTitle = "New Title";
    history.AddAndExecuteCommand(std::move(std::move(std::make_unique<SetTitleCommand>(title, newTitle))));

    EXPECT_TRUE(history.CanUndo());
    EXPECT_FALSE(history.CanRedo());

    history.Undo();
    EXPECT_FALSE(history.CanUndo());
    EXPECT_TRUE(history.CanRedo());
}

TEST(HistoryTests, UndoAndRedoSucess)
{
    History history;
    std::string title = "Original Title";
    std::string newTitle = "New Title";
    history.AddAndExecuteCommand(std::move(std::make_unique<SetTitleCommand>(title, newTitle)));

    history.Undo();
    EXPECT_FALSE(history.CanUndo());
    EXPECT_TRUE(history.CanRedo());

    history.Redo();
    EXPECT_TRUE(history.CanUndo());
    EXPECT_FALSE(history.CanRedo());
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}