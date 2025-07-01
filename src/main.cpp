#include "include/input/inputCollector.hpp"
#include "include/render/button.hpp"
#include "include/render/field.hpp"
#include "include/render/text.hpp"

#include <cstdio>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <thread>

void init() { _setmode (_fileno (stdout), _O_U16TEXT); }

int	 main() {
	 init();
	 std::wcout << L"\033[H\033[0J";
	 int	 MAX_WIDTH = 0, MAX_HEIGHT = 0;
	 Field	 login (0, 0, MAX_WIDTH, MAX_HEIGHT, nullptr, "LOGIN");
	 Object *label = new Text (0, 3, &login, "Username", "Username: ", TYPE::NORMAL, false);
	 login.add_object (label);
	 Object *passlabel = new Text (0, 8, &login, "Password", "Password: ", TYPE::NORMAL, false);
	 login.add_object (passlabel);
	 Object *loginButton =
		 new Button (login.width() / 2, login.height() / 2, &login, "BUTTON", "LOGIN [L]");
	 login.add_object (loginButton);
	 login.add_object (new Field (label->cord_x() + label->width() + 5, label->cord_y(), 10, 1, &login, "TEXTFIELD"));
	 login.add_object (new Field (passlabel->cord_x() + passlabel->width() + 5, passlabel->cord_y(), 10, 1, &login,
								 "FIELD"));

	 while (1) {
		 InputCollector::Instance().update();
		 Event e;
		 while (InputCollector::Instance().pollEvent (&e)) {
			 if (e.type == WINDOW_RESIZE) {
				 MAX_WIDTH	= e.win_size.width - 1;
				 MAX_HEIGHT = e.win_size.height - 1;
			 }
			 login.set_w (MAX_WIDTH);
			 login.set_h (MAX_HEIGHT);
			 loginButton->set_x (login.width() / 2 - loginButton->width() / 2);
			 loginButton->set_y (login.height() / 2 - loginButton->height() / 2);
		 }
		 login.render();
		 InputCollector::Instance().reset();
		 std::this_thread::sleep_for (std::chrono::milliseconds (33));
	 }
}
