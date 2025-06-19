#ifndef INCLUDE_CORE_SING_TRANS_HPP_INCLUDED
#define INCLUDE_CORE_SING_TRANS_HPP_INCLUDED

#include <string>

struct Trans {
	int			ID;		// ID of Tansaction
	int			UserID; // User that performed transaction
	int			BookID; // Book borrowed or returned
	std::string Bdate;	// Borrowed date of book
	std::string RDate;	// Returned date of book. Empty string if not returned
};

#endif