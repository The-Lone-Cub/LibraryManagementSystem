// InputCollector.hpp
// ===================
//
// This class provides a singleton interface for collecting and managing input events (keyboard,
// mouse, window resize) from the Windows OS. It uses low-level hooks to capture input events
// globally and stores them in a stack for polling.
//
// ! NOTE: This class is Windows-specific due to its use of WinAPI hooks and types.
//
// ? Usage:
//   - Use InputCollector::Instance() to access the singleton.
//   - Call update() regularly (e.g., once per frame) to process new events.
//   - Use pollEvent() to retrieve and remove the latest event from the stack.
//   - Use reset() to clear all pending events.
//
// * Event types and structures are defined below for clarity.

#ifndef INCLUDE_INPUT_INPUTCOLLECTOR_HPP
#define INCLUDE_INPUT_INPUTCOLLECTOR_HPP

#include <chrono>
#include <vector>
#include <windows.h>

// TODO: Add more event types if needed
/// @enum InputEventType: Represents the type of input event captured
// * KEY_DOWN, KEY_UP: Keyboard events
// * MOUSE_MOVE, MOUSE_DOWN, MOUSE_UP: Mouse movement and button events
// * MOUSE_SCROLL, MOUSE_HSCROLL: Mouse wheel events (vertical/horizontal)
// * WINDOW_RESIZE: Console window resize event
enum InputEventType
{
	KEY_DOWN,
	KEY_UP,
	MOUSE_MOVE,
	MOUSE_DOWN,
	MOUSE_UP,
	MOUSE_SCROLL,
	MOUSE_HSCROLL,
	WINDOW_RESIZE
};

/// @enum MouseButton: Mouse button codes (left/right)
enum MouseButton
{
	MS_LEFT	 = 0,
	MS_RIGHT = 1
};

/// @struct KeyEvent: Keyboard event data
struct KeyEvent {
		int code;	 // * Integer code of key.
};

/// @struct ResizeEvent: Window resize event data
struct ResizeEvent {
		int width, height;	  // * New window size in characters
};

/// @struct MouseScroll: Mouse wheel event data
struct MouseScroll {
		int steps;	  // * Number of scroll notches (positive/negative)
		int x, y;	  // * Mouse position at event
};

/// @struct MouseEvent: Mouse button/move event data
struct MouseEvent {
		int x, y;	   // * Mouse position
		int button;	   // * MouseButton enum value
};

/// @struct Event: Unified event structure for all input types
struct Event {
		InputEventType type;	// * Type of event
		std::chrono::time_point<std::chrono::steady_clock>
			timestamp;	  // * Time event was captured

		union {
				KeyEvent	key;		 // * Keyboard event data
				MouseEvent	mouse;		 // * Mouse event data
				ResizeEvent win_size;	 // * Window resize event data
				MouseScroll scroll;		 // * Mouse scroll event data
		};
};

/// @class InputCollector
// ! Singleton class for collecting and polling input events
//
// # Usage Example:
//   InputCollector &ic = InputCollector::Instance();
//   ic.update();
//   Event e;
//   while (ic.pollEvent(&e)) { /* handle event */ }
class InputCollector {
	private:
		std::vector<Event> events;		 // * Stack of pending events (LIFO)
		int				   pollIndex;	 // * Shows current event.
		HHOOK			   keyboard;	 // * Keyboard hook handle

		// ! Private constructor/destructor for singleton pattern
		InputCollector();
		~InputCollector();

	public:
		/// @brief Get the singleton instance
		static InputCollector &Instance() {
			static InputCollector inst;
			return inst;
		}

		/// @brief Log a new event (called by hooks)
		void logEvent (const Event &e) { events.push_back (e); }

		/// @brief Update input state, process new events
		// ! Call this once per frame or input polling cycle
		void update();

		/// @brief Poll the latest event (returns true if event was available)
		bool pollEvent (Event *e);

		/// @brief Clear all pending events
		void reset() {
			events.clear();
			pollIndex = 0;
		}
};

#endif
