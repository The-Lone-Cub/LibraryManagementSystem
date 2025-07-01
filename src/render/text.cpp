#include "include/render/text.hpp"

#include "include/commons.hpp"
#include "include/input/inputCollector.hpp"

#include <iostream>

void Text::update() {
	if (!editable) return;
	Event e;
	while (InputCollector::Instance().pollEvent (&e)) {
		if (e.type == MOUSE_DOWN) {
			if ((e.mouse.x >= get_x() && e.mouse.x <= get_x() + width()) &&
				(e.mouse.y >= get_y() && e.mouse.y <= get_y() + height()) &&
				e.mouse.button == MS_LEFT)
				focus = true;
			else focus = false;
		}
		if (!focus) continue;
		if (e.type == KEY_DOWN) {
			if (e.key.code == '\b') {
				if (!data.empty()) data.pop_back();
			} else if (placeholder) {
				data		= std::string(1, e.key.code);
				placeholder = false;
			} else if (data.empty() && !ph_data.empty()) {
				data		= ph_data;
				placeholder = true;
			} else {
				data += std::string(1, e.key.code);
			}
		}
	}
}

void Text::render() const {
	CUI_SET (get_x(), get_y());
	for (auto i = 0ULL; i < data.length(); ++i)
		if (data [i] != '\n')
			std::wcout << (placeholder ? CUI_FORE (CUI_DARK_GREY) : CUI_FORE (CUI_WHITE))
					   << (t == TYPE::NORMAL ? std::wstring (1, data [i]) : L"\u2620 ")
					   << (i >= data.length() - 1 ? t == TYPE::NORMAL ? L"" : L"  " : L"")
					   << CUI_RESET;
}
