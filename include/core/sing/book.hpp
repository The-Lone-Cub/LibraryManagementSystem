#ifndef INCLUDE_CORE_SING_BOOK_HPP_INCLUDED
#define INCLUDE_CORE_SING_BOOK_HPP_INCLUDED

#include <string>

struct Book {
	int			ID;		  // Book ID
	std::string title;	  // Book title
	int			author;	  // Book author
	int			quantity; // Quantity of copies
};

#endif