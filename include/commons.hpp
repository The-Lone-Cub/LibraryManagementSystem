#ifndef INCLUDE_COMMONS_HPP
#define INCLUDE_COMMONS_HPP

#include <string>

//? Escape sequence initiator for terminal control
#define CUI_ESC std::wstring (L"\033")

//? Move cursor to (x, y) on terminal
//* If x or y is 0, defaults to 1 (top-left corner)
// Usage: CUI_SET(10, 5);  // Moves cursor to column 10, row 5
#define CUI_SET(x, y) std::wcout << CUI_ESC << L"[" << ((y) + 1) << L";" << ((x) + 1) << L"H"

//? Set text foreground or background color
// Usage: std::wcout << CUI_FORE(CUI_RED) << L"Hello" << CUI_RESET;
//! Must be used inside an output stream like std::wcout
#define CUI_FORE(x) CUI_ESC + L"[38;5;" + std::to_wstring (x) + L"m"
#define CUI_BACK(x) CUI_ESC + L"[48;5;" + std::to_wstring (x) + L"m"

//? Reset all terminal formatting (colors, styles, etc.)
//* Always use after printing colored text to avoid color bleeding
#define CUI_RESET CUI_ESC + L"[0m"

//? Converts RGB values (0–255) to terminal color index (0–255)
// Usage: CUI_FORE(CUI_RGB(255, 0, 0)) for bright red
constexpr int CUI_RGB (int r, int g, int b) {
	return (16 + ((r / 17) * 12) + ((g / 51) * 6) + b / 51);
}

struct CUI_Border {
		std::wstring tl, tr, bl, br, hor, ver, sh;
};

inline constexpr CUI_Border CUI_BORDER_NORMAL  = {L"\u250C", L"\u2510", L"\u2514", L"\u2518",
												  L"\u2500", L"\u2502", L"\u2591"};
inline constexpr CUI_Border CUI_BORDER_FOCUSED = {L"\u2554", L"\u2557", L"\u255A", L"\u255D",
												  L"\u2550", L"\u2551", L"\u2592"};

//----------------------
//* COLOR DEFINITIONS *
//----------------------

//! Colors are mapped to 256-color terminal codes
//? You can use any of these as arguments to CUI_FORE(...) or CUI_BACK(...)

// --- Reds ---
#define CUI_DARK_RED  88	 // RGB(135, 0, 0)     #870000
#define CUI_RED		  160	 // RGB(215, 0, 0)     #d70000
#define CUI_LIGHT_RED 203	 // RGB(255, 95, 95)   #ff5f5f

// --- Greens ---
#define CUI_DARK_GREEN	22	   // RGB(0, 95, 0)      #005f00
#define CUI_GREEN		34	   // RGB(0, 175, 0)     #00af00
#define CUI_LIGHT_GREEN 120	   // RGB(135, 255, 135) #87ff87

// --- Blues ---
#define CUI_DARK_BLUE  18	 // RGB(0, 0, 135)     #000087
#define CUI_BLUE	   21	 // RGB(0, 0, 255)     #0000ff
#define CUI_LIGHT_BLUE 81	 // RGB(95, 215, 255)  #5fd7ff

// --- Yellows ---
#define CUI_DARK_YELLOW	 100	// RGB(135, 135, 0)   #878700
#define CUI_YELLOW		 226	// RGB(255, 255, 0)   #ffff00
#define CUI_LIGHT_YELLOW 229	// RGB(255, 255, 175) #ffffaf

// --- Oranges ---
#define CUI_DARK_ORANGE	 130	// RGB(175, 95, 0)    #af5f00
#define CUI_ORANGE		 166	// RGB(215, 95, 0)    #d75f00
#define CUI_LIGHT_ORANGE 215	// RGB(255, 175, 95)  #ffaf5f

// --- Purples ---
#define CUI_DARK_PURPLE	 54		// RGB(95, 0, 135)    #5f0087
#define CUI_PURPLE		 93		// RGB(135, 0, 255)   #8700ff
#define CUI_LIGHT_PURPLE 183	// RGB(215, 175, 255) #d7afff

// --- Pinks ---
#define CUI_DARK_PINK  125	  // RGB(175, 0, 95)    #af005f
#define CUI_PINK	   200	  // RGB(255, 0, 215)   #ff00d7
#define CUI_LIGHT_PINK 218	  // RGB(255, 175, 215) #ffafd7

// --- Browns ---
#define CUI_DARK_BROWN	52	   // RGB(95, 0, 0)      #5f0000
#define CUI_BROWN		94	   // RGB(135, 95, 0)    #875f00
#define CUI_LIGHT_BROWN 180	   // RGB(215, 175, 135) #d7af87

// --- Cyans ---
#define CUI_DARK_CYAN  30	  // RGB(0, 135, 135)   #008787
#define CUI_CYAN	   51	  // RGB(0, 255, 255)   #00ffff
#define CUI_LIGHT_CYAN 159	  // RGB(175, 255, 255) #afffff

// --- Greys ---
#define CUI_DARK_GREY  234	  // RGB(28, 28, 28)    #1c1c1c
#define CUI_GREY	   240	  // RGB(88, 88, 88)    #585858
#define CUI_LIGHT_GREY 250	  // RGB(188, 188, 188) #bcbcbc

// --- Blacks ---
#define CUI_BLACK		 0		// RGB(0, 0, 0)       #000000
#define CUI_SOFTER_BLACK 232	// RGB(8, 8, 8)       #080808
#define CUI_DIM_BLACK	 233	// RGB(18, 18, 18)    #121212

// --- Whites ---
#define CUI_WHITE		 255	// RGB(238, 238, 238) #eeeeee
#define CUI_BRIGHT_WHITE 15		// RGB(255, 255, 255) #ffffff
#define CUI_SOFT_WHITE	 231	// RGB(255, 255, 255) #ffffff

// --- Miscellaneous Colors ---
#define CUI_GOLD	  220
#define CUI_MINT	  121
#define CUI_SKY_BLUE  117
#define CUI_TEAL	  37
#define CUI_MAGENTA	  201
#define CUI_VIOLET	  129
#define CUI_OLIVE	  100
#define CUI_TURQUOISE 80
#define CUI_LAVENDER  183

#endif	  // INCLUDE_COMMONS_HPP
