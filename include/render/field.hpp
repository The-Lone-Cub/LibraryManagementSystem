#ifndef INCLUDE_RENDER_FIELD_HPP
#define INCLUDE_RENDER_FIELD_HPP

#include "object.hpp"

class Field: public Object {
	public:
		Field (int x, int y, int w, int h, Object *ow, std::string ID):
			Object (x, y, w, h, ow, ID) { }

		void update() override { }

		void render() const override;
};

#endif
