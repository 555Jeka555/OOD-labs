#include <iostream>
#include <memory>

// Интерфейс документа
class Document {
public:
    virtual void open() = 0;
    virtual void save() = 0;
    virtual ~Document() = default;
};

// Текстовый документ
class TextDocument : public Document {
public:
    void open() override {
        std::cout << "Opening Text Document..." << std::endl;
    }

    void save() override {
        std::cout << "Saving Text Document..." << std::endl;
    }
};

// Табличный документ
class SpreadsheetDocument : public Document {
public:
    void open() override {
        std::cout << "Opening Spreadsheet Document..." << std::endl;
    }

    void save() override {
        std::cout << "Saving Spreadsheet Document..." << std::endl;
    }
};

// Абстрактный класс приложения
class Application {
public:
    virtual std::unique_ptr<Document> createDocument() = 0;

    void newDocument() {
        std::unique_ptr<Document> doc = createDocument();
        doc->open();
        doc->save();
    }

    virtual ~Application() = default;
};

// Приложение для работы с текстовыми документами
class TextApplication : public Application {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<TextDocument>();
    }
};

// Приложение для работы с табличными документами
class SpreadsheetApplication : public Application {
public:
    std::unique_ptr<Document> createDocument() override {
        return std::make_unique<SpreadsheetDocument>();
    }
};

// Клиентский код
int main() {
    std::unique_ptr<Application> app;

    // Используем TextApplication
    app = std::make_unique<TextApplication>();
    app->newDocument();

    // Используем SpreadsheetApplication
    app = std::make_unique<SpreadsheetApplication>();
    app->newDocument();

    return 0;
}