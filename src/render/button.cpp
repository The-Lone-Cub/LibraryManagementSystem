#include "include/render/button.hpp"

#include "include/commons.hpp"

#include <iostream>


void Button::render() const {
	std::vector<Object *> objs = get_objects();
	for (const auto &i : objs) i->render();

	CUI_Border b = focus ? CUI_BORDER_FOCUSED : CUI_BORDER_NORMAL;

	// Top
	CUI_SET (get_x(), get_y());
	std::wcout << b.tl;	  // Top left corner
	for (int i = 0; i < objs [0]->width() + 2 * padding; ++i)
		std::wcout << b.hor;	  // Top border
	std::wcout << b.tr;		  // Top right corner

	// Mid
	CUI_SET (get_x(), get_y() + 1);					  // Go down one line
	std::wcout << b.ver;	  // Left border
	CUI_SET (get_x() + objs [0]->width() + 1 + 2 * padding,
			 get_y() + 1);	  // Go to the right side of the button
	std::wcout << b.ver << b.sh << b.sh;   // Right border plus shadowing

	// Bottom
	CUI_SET (get_x(), get_y() + 2);					  // Go down two lines
	std::wcout << b.bl;	  // Bottom left corner
	for (int i = 0; i < objs [0]->width() + 2 * padding; ++i)
		std::wcout << b.hor;	  // Bottom button border
	std::wcout << b.br << b.sh << b.sh;	  // Bottom right border plus shadowing

	// Shadow
	CUI_SET (get_x() + 1, get_y() + 3);	   // Move three lines down and one character to the right
	for (int i = 0; i < objs [0]->width() + 3 + 2 * padding; ++i)
		std::wcout << b.sh;	  // Bottom shadowing
}
