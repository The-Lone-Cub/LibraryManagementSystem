#ifndef INCLUDE_RENDER_BUTTON_HPP
#define INCLUDE_RENDER_BUTTON_HPP

#include "include/render/object.hpp"
#include "include/render/text.hpp"
#include <functional>

class Button: public Object {
	private:
		int padding;
		std::function<void()> callback;
	public:
		Button (int x, int y, Object *ow, std::string ID, std::string label, int padding = 2, std::function<void()> callback = []() {}):
			Object (x, y, label.length() + 2 + 2 * padding, 4, ow, ID), padding (padding), callback(callback) {
			Object *l = new Text (padding, 0, this, "LABEL", label);
			this->add_object (l);
			w = l->width() + 4 + (2 * padding);
			// Use callback to avoid unused parameter warning (optional: remove if not needed)
			// callback();
		}

		void update() override { }

		void render() const override;
};

#endif
