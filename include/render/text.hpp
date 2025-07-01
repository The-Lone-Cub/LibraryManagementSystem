#ifndef INCLUDE_RENDER_TEXT_HPP
#define INCLUDE_RENDER_TEXT_HPP

#include "object.hpp"

enum class TYPE
{
	NORMAL,
	HIDDEN
};

class Text: public Object {
		std::string data;
		std::string ph_data;
		TYPE		t;
		bool		placeholder;
		bool editable;

	public:
		Text (int x, int y, Object *ow, std::string ID, std::string data = "",
			  TYPE t = TYPE::NORMAL, bool editable = true, bool ph = false):
			Object (x, y, data.length(), 1, ow, ID), data (data), t (t), placeholder (ph), editable(editable) {
			if (t == TYPE::HIDDEN) w += data.length();
			if (placeholder) ph_data = data;
		}

		void update() override;

		void render() const override;

		int	 get_width() const { return w; }
};

#endif
