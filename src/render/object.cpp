#include "include/render/object.hpp"

Object::~Object() {
	for (auto &o : objects) delete o;
	objects.clear();
}

void Object::add_object (Object *obj) {
	objects.push_back (obj);
	if (obj->get_x() + obj->w > get_x() + w) w = (obj->get_x() + obj->w) - get_x();
	if(obj->get_y() + obj->h > get_y() + h) h = (obj->get_y() + obj->h) - get_y();
}

void Object::remove_object (std::string id) {
	size_t i;
	for (i = 0; i < objects.size(); ++i)
		if (objects [i]->ID == id) break;
	if (i == objects.size()) return;
	objects.erase (objects.begin() + i);
}

Object *Object::edit_object (std::string id) {
	for (auto i = 0ULL; i < objects.size(); ++i)
		if (objects [i]->ID == id) return objects [i];
	return nullptr;
}