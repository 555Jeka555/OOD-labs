#include "Library.h"
#include <format>

ostream& operator<<(ostream& out, const Book& book) {
      out << std::format(R"("{}" by {}, {})",
        book.GetTitle(), book.GetAuthor(), book.GetPublicationYear());
      return out;
}


void PrintBooks(IBookIterator& iter)
{
      for (; iter.HasBook(); iter.Next())
      {
            std::cout << iter.GetBook() << std::endl;
          }
}


int main()
{
    Library library;
      library.AddBook(Book{ "Moby Dick", "Herman Melville", 1851 });
      library.AddBook(Book{ "White Fang", "Jack London", 1906 });
      library.AddBook(Book{ "Harry Potter and the Philosopher's Stone", "Joanne Rowling", 1997 });
      library.AddBook(Book{ "Harry Potter and the Chamber of Secrets", "Joanne Rowling", 1998 });

      PrintBooks(*library.GetAllBooks());
      if (const auto joanneRowlingBooks = library.FindAuthorBooks("Joanne Rowling"))
      {
            std::cout << "---" << std::endl;
            PrintBooks(*joanneRowlingBooks);
          }

}