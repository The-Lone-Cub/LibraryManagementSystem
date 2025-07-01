#include "include/render/field.hpp"

#include "include/commons.hpp"

#include <iostream>
#include <vector>

void Field::render() const {
	std::vector<Object *> objs = get_objects();
	for (const auto &o : objs) o->render();
	CUI_Border b = focus ? CUI_BORDER_FOCUSED : CUI_BORDER_NORMAL;

	// Top
	CUI_SET (get_x(), get_y());
	std::wcout << b.tl;
	for (auto i = 0; i < w - 1; ++i) std::wcout << b.hor;
	std::wcout << b.tr;

	// Middle
	for (int i = 1; i < h - 1; ++i) {
		CUI_SET (get_x(), get_y() + i);
		std::wcout << b.ver;
		CUI_SET (get_x() + w, get_y() + i);
		std::wcout << b.ver;
	}

	// Bottom
	CUI_SET (get_x(), get_y() + h);
	std::wcout << b.bl;
	for (auto i = 0; i < w - 1; ++i) std::wcout << b.hor;
	std::wcout << b.br;
}
