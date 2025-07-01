#include "include/input/inputCollector.hpp"

#include <chrono>
#include <consoleapi.h>
#include <consoleapi2.h>
#include <consoleapi3.h>
#include <minwindef.h>
#include <processenv.h>
#include <wincontypes.h>
#include <windows.h>

bool vkToAscii (int vkCode, char *outChar) {
	BYTE keyboardState [256];
	if (!GetKeyboardState (keyboardState)) return false;

	// Force Shift and Caps Lock manually
	if (GetAsyncKeyState (VK_SHIFT) & 0x8000) keyboardState [VK_SHIFT] |= 0x80;
	if (GetAsyncKeyState (VK_CAPITAL) & 0x0001) keyboardState [VK_CAPITAL] |= 0x01;
	if (GetAsyncKeyState (VK_BACK) & 0x8000) keyboardState [VK_BACK] |= 0x80;

	UINT scanCode = MapVirtualKey (vkCode, MAPVK_VK_TO_VSC);
	WORD ascii [2];
	int	 result = ToAscii (vkCode, scanCode, keyboardState, ascii, 0);

	if (result == 1) {
		*outChar = static_cast<char> (ascii [0]);
		return true;
	}

	return false;
}

// ! Low-level keyboard hook callback
// * Captures global keyboard events and logs them as Event objects
LRESULT CALLBACK LowLevelKeyboardProc (int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HC_ACTION) {
		KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *) lParam;
		Event			 e;
		if (vkToAscii (p->vkCode, (char *) &e.key.code)) {

			e.timestamp = std::chrono::steady_clock::now();

			if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) e.type = KEY_DOWN;
			else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) e.type = KEY_UP;

			// ? Log the keyboard event to the InputCollector
			InputCollector::Instance().logEvent (e);
		}
	}
	return CallNextHookEx (nullptr, nCode, wParam, lParam);
}

// ! Helper function to get the current console window size (in characters)
void GetConsoleSize (int *width, int *height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi)) {
		*width	= csbi.srWindow.Right - csbi.srWindow.Left + 1;
		*height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
}

// ! InputCollector constructor
// * Installs low-level keyboard and mouse hooks
InputCollector::InputCollector() {
	keyboard  = SetWindowsHookEx (WH_KEYBOARD_LL, LowLevelKeyboardProc, nullptr, 0);
	pollIndex = 0;

	SetConsoleMode (GetStdHandle (STD_INPUT_HANDLE),
					ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);
}

// ! InputCollector destructor
// * Removes installed hooks
InputCollector::~InputCollector() {
	if (keyboard) UnhookWindowsHookEx (keyboard);
}

// ! Update input state and process new events
// * Checks for window resize and pumps Windows messages to trigger hooks
void InputCollector::update() {
	static int ls_width = 0, ls_height = 0;
	int		   width, height;
	GetConsoleSize (&width, &height);
	if (width != ls_width || height != ls_height) {
		Event e;
		e.timestamp		  = std::chrono::steady_clock::now();
		e.type			  = WINDOW_RESIZE;
		e.win_size.width  = width;
		e.win_size.height = height;
		ls_width		  = width;
		ls_height		  = height;
		logEvent (e);
	}

	INPUT_RECORD records [128];
	DWORD		 eventsRead;

	DWORD		 eventsAvailable = 0;
	GetNumberOfConsoleInputEvents (GetStdHandle (STD_INPUT_HANDLE), &eventsAvailable);

	if (eventsAvailable > 0) {
		PeekConsoleInput (GetStdHandle (STD_INPUT_HANDLE), records, 128, &eventsRead);
		if (eventsRead > 0) {
			ReadConsoleInput (GetStdHandle (STD_INPUT_HANDLE), records, 128, &eventsRead);
			for (DWORD i = 0; i < eventsRead; ++i) {
				if (records [i].EventType == MOUSE_EVENT) {
					const MOUSE_EVENT_RECORD mouse = records [i].Event.MouseEvent;
					Event					 e;
					e.timestamp = std::chrono::steady_clock::now();
					if (mouse.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
						e.type		   = MOUSE_DOWN;
						e.mouse.button = 0;
						e.mouse.x	   = mouse.dwMousePosition.X;
						e.mouse.y	   = mouse.dwMousePosition.Y;
					} else if (mouse.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
						e.type		   = MOUSE_DOWN;
						e.mouse.button = 1;
						e.mouse.x	   = mouse.dwMousePosition.X;
						e.mouse.y	   = mouse.dwMousePosition.Y;
					} else if (mouse.dwEventFlags == MOUSE_WHEELED) {
						e.type		   = MOUSE_SCROLL;
						e.scroll.steps = HIWORD (mouse.dwButtonState) / WHEEL_DELTA;
						e.scroll.x	   = mouse.dwMousePosition.X;
						e.scroll.y	   = mouse.dwMousePosition.Y;
					} else {
						e.type	  = MOUSE_MOVE;
						e.mouse.x = mouse.dwMousePosition.X;
						e.mouse.y = mouse.dwMousePosition.Y;
					}
				}
			}
		}
	}

	// * Pump Windows messages so hooks are called
	MSG msg;
	while (PeekMessage (&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}
}

// ! Poll the latest input event
// ? Returns true if an event was available, false otherwise
bool InputCollector::pollEvent (Event *e) {
	if (pollIndex < (int) events.size()) {
		*e = events [pollIndex];
		++pollIndex;
		return true;
	} else {
		pollIndex = 0;
		return false;
	}
}
