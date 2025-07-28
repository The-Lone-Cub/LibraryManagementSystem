#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

void RegistrationScreen(ftxui::ScreenInteractive& screen, std::string& next_screen) {
    using namespace ftxui;

    Component ui = Renderer([&] {
        return window(
            text("Registration Form") | bold,
            text("Details will be brought in with time. Please wait...")
        );
    });

    Component list = CatchEvent(ui, [&](Event event) {
        if(event == Event::Escape) {
            next_screen = "login";
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    });

    screen.Loop(list);
}

void LoginScreen(ftxui::ScreenInteractive& screen, std::string& next_screen) {
    using namespace ftxui;

    std::string username, password;
    Component user = Input(&username, "John Doe");
    Component pass = Input(&password, "admin");

    Component submit = Button("SUBMIT", [&]{next_screen = "submit"; screen.ExitLoopClosure()();});
    Component regist = Button("REGISTER", [&]{next_screen = "register"; screen.ExitLoopClosure()();});
    Component reset = Button("RESET", [&]{username = ""; password = "";});

    Component buttons = Container::Horizontal({regist, submit, reset});
    int child_index = 0;
    Component input_cont = Container::Vertical({user, pass, buttons}, &child_index);
    Component input = CatchEvent(input_cont, [&](Event event) {
        if(event != Event::Return) return false;

        if(child_index == 0 || child_index == 1) {
            submit->OnEvent(Event::Return);
            return true;
        }
        return false;
    });


    Component ui = Renderer(input, [&] {
        return window(
            text("Login") | bold,
            vbox(
                        hbox(
                            text("Username: "),
                            user->Render() | size(WIDTH, EQUAL, 20)),
                        hbox(
                            text("Password: "),
                            pass->Render() | size(WIDTH, EQUAL, 20)),
                        separator(),
                        hbox(
                            regist->Render() | size(WIDTH, EQUAL, 10),
                            submit->Render() | size(WIDTH, EQUAL, 10),
                            reset->Render() | size(WIDTH, EQUAL, 10)
                        ) | center
            )
        ) | center;
    });

    screen.Loop(ui);
}

void SubmissionScreen(ftxui::ScreenInteractive& screen, std::string& next_screen) {
    using namespace ftxui;

    Component ui = Renderer([] {
        return window(
            text("Main window"),
            text("This contains the actual page")
        );
    });

    Component ev = CatchEvent(ui, [&](Event event) {
        if(event == Event::Escape) {
            next_screen = "null";
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
    });

    screen.Loop(ev);
}

int main() {
    using namespace ftxui;

    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    std::string next_screen = "login";

    while(next_screen != "null") {
        if(next_screen == "login") {
            LoginScreen(screen, next_screen);
        } else if (next_screen == "register") {
            RegistrationScreen(screen, next_screen);
        } else if(next_screen == "submit") {
            SubmissionScreen(screen, next_screen);
        } else break;
    }
    return 0;
}