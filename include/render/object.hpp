#ifndef INCLUDE_RENDER_OBJECT_HPP
#define INCLUDE_RENDER_OBJECT_HPP

#include <string>
#include <vector>

class Object {
	private:
		/**
		 *? Top most parent in heirachy will have their owner as null and x
		 *? and y coordinates will directly be relative to window
		 */
		Object				 *owner;	  // Parent object.
		std::vector<Object *> objects;	  // Stores children objects

		std::string			  ID;	 // Object's ID

	protected:
		int x, y;	 // x and y position of object relative to parent
		int w, h;	 // Stores width and height of object

		/**
		 *! All child object must have their width, height as well as positions less than or equal
		 *! to the parent's. Else, the object will be rendered improperly
		 */

		bool focus;	   // stores whether object is in focus or not

		int	 get_x() const {
			 return owner ? owner->get_x() + x + 1 : x;
		}	 // return absolute value of x

		int get_y() const {
			return owner ? owner->get_y() + y + 1 : y;
		}	 // return absolute value of y

		std::vector<Object *> get_objects() const { return objects; }

	public:
		Object (int x, int y, int w, int h, Object *ow, std::string ID):
			owner (ow), ID (ID), x (x), y (y), w (w), h (h), focus (false) {
			objects = {};
		}

		virtual ~Object();

		// Object interactions
		void	add_object (Object *obj);
		void	remove_object (std::string id);
		Object *edit_object (std::string id);

		//? Placeholder function to handle input events and internal data change in case any exists
		virtual void update() = 0;

		//? Render both self and children
		virtual void render() const = 0;

		int			 width() const { return w; }

		int			 height() const { return h; }

		void		 switch_focus() { focus = !focus; }

		void		 set_x (int x) { this->x = x; }

		void		 set_y (int y) { this->y = y; }

		void		 set_w (int w) { this->w = w; }

		void		 set_h (int h) { this->h = h; }

		int			 cord_x() const { return x; }

		int			 cord_y() const { return y; }
};

#endif
