#ifndef EXAM_LIBRARY_H
#define EXAM_LIBRARY_H

#include <unordered_map>
#include <deque>
#include <memory>
#include "IBookIterator.h"
#include "Book.h"

class Library {
private:
    class DequeBookIterator : public IBookIterator {
    public:
        using Coll = std::deque<Book>;
        using Iter = Coll::const_iterator;

        DequeBookIterator() = default;

        DequeBookIterator(Iter current, Iter end)
                : m_current(current), m_end(end) {}

        const Book &GetBook() const override {
            return HasBook() ? *m_current : throw std::logic_error("Invalid iterator");
        }

        bool HasBook() const override { return m_current != m_end; }

        void Next() override {
            if (!HasBook())
                throw std::logic_error("Invalid iterator");
            ++m_current;
        }

    private:
        Iter m_current;
        Iter m_end;
    };

    using BookByTitle = std::unordered_map<std::string, const Book *>;
    class BookByTitleIterator : public IBookIterator {
    public:
        using Iter = BookByTitle::const_iterator;

        BookByTitleIterator() = default;

        BookByTitleIterator(Iter current, Iter end)
                : m_current(current), m_end(end) {}

        const Book &GetBook() const override {
            return HasBook() ? *m_current->second : throw std::logic_error("Invalid iterator");
        }

        bool HasBook() const override { return m_current != m_end; }

        void Next() override {
            if (!HasBook())
                throw std::logic_error("Invalid iterator");
            ++m_current;
        }

    private:
        Iter m_current;
        Iter m_end;
    };

public:

    std::unique_ptr<IBookIterator> GetAllBooks() const {
        return std::make_unique<DequeBookIterator>(m_books.begin(), m_books.end());
    }

    std::unique_ptr<IBookIterator> FindAuthorBooks(const string &author) const {
        auto it = m_authorBooks.find(author);
        return it != m_authorBooks.end()
               ? make_unique<BookByTitleIterator>(it->second.begin(), it->second.end())
               : make_unique<BookByTitleIterator>();
    }

    void AddBook(Book book) {
            const auto& b = m_books.emplace_back(std::move(book));
            auto& authorBooks = m_authorBooks[b.GetAuthor()];
            if (!authorBooks.try_emplace(b.GetTitle(), &b).second) {
                  m_books.pop_back();
                  throw std::invalid_argument("Book already exists");
                }
          }


private:
    std::deque<Book> m_books;
    std::unordered_map<std::string, BookByTitle> m_authorBooks;
};


#endif //EXAM_LIBRARY_H
