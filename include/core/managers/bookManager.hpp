#ifndef INCLUDE_CORE_MANAGERS_BOOKMANAGER_HPP_INCLUDED
#define INCLUDE_CORE_MANAGERS_BOOKMANAGER_HPP_INCLUDED

#include "../sing/book.hpp"
#include <vector>

enum BOOK_SEARCH_TYPE { ID, TITLE, AUTHOR, YEAR };

class BookManager {
    private:
	  std::vector<Book> books;
	  std::string		path;

	public:
        static BookManager& Instance() {
			static BookManager inst = BookManager();
			return inst;
		}

		void load(const std::string& path);
		void			  save();
		std::vector<Book> getBooks(BOOK_SEARCH_TYPE s, const std::string& query);
		void			  addBook(const Book& b) { books.push_back(b); }
		void			  removeBook(int ID);
		void			  editBook(int ID, const Book& b);
};

#endif