#ifndef EXAM_BOOK_H
#define EXAM_BOOK_H

#include "iostream"
#include "string"

using namespace std;

class Book {
public:
      Book(string title, string author, int publicationYear)
        : m_title(std::move(title))
        , m_author(std::move(author))
        , m_publicationYear(publicationYear)
      {
          }

      [[nodiscard]] string GetTitle() const { return m_title; }
      [[nodiscard]] string GetAuthor() const { return m_author; }
      [[nodiscard]] int GetPublicationYear() const { return m_publicationYear; }
    private:
      string m_title;
      string m_author;
      int m_publicationYear;
};


#endif //EXAM_BOOK_H
