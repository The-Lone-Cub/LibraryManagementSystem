#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <thread>

struct user {
    std::string username;
    std::string password;
};

std::vector<user> Users;

ftxui::ButtonOption Style() {
    using namespace ftxui;
    auto option = ButtonOption::Animated();
    option.transform = [](const EntryState& s) {
        auto element = text(s.label);
        if(s.focused) {
            element |= bold;
        }
        return element | center | borderEmpty | flex;
    };
    return option;
}

void RegistrationScreen(ftxui::ScreenInteractive& screen, std::string& next_screen) {
    using namespace ftxui;

    std::string first, last, username, password, output;
    Component first_input = Input(&first, "John");
    Component last_input = Input(&last, "Doe");
    Component username_input = Input(&username, "user123");
    InputOption passfield;
    passfield.password = true;
    Component password_input = Input(&password, "admin", passfield);

    Component submit = Button("SUBMIT", [&] {
        if(first.empty() || last.empty() || username.empty() || password.empty()) {
            output = "Empty fields detected. Submission denied.";
        } else {
            output = username + " registered successfully. Returning to login screen...";
            Users.push_back({username, password});
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(3s);
            next_screen = "login";
            screen.ExitLoopClosure()();
        }
    }, Style());
    Component clear = Button("RESET", [&] {first = last = username = password = output = "";}, Style());
    int childform = 0, childbut = 0;
    Component buts = Container::Horizontal({submit, clear}, &childbut);
    Component form = Container::Vertical({
        first_input, last_input, username_input, password_input, buts
    }, &childform);

    Component ui = Renderer(form, [&] {
        return window(
            text("Registration Form") | bold,
            vbox({
                    hbox({
                        text("First Name: "),
                        first_input->Render() | size(WIDTH, EQUAL, 20)
                        }),
                    hbox({
                        text("Last Name: "),
                        last_input->Render() | size(WIDTH, EQUAL, 20)
                    }),
                    hbox({
                        text("Username: "),
                        username_input->Render() | size(WIDTH, EQUAL, 20)
                    }),
                    hbox({
                        text("Password: "),
                        password_input->Render() | size(WIDTH, EQUAL, 20)
                    }),
                    separator(),
                    hbox({
                        submit->Render() | flex,
                        clear->Render() | flex
                    }),
                    text(output) | color((output.substr(0, 5) != "Empty" ? Color::Green : Color::Red))
            })
        ) | center;
    });

    Component list = CatchEvent(ui, [&](Event event) {
        if(event == Event::Escape) {
            next_screen = "login";
            screen.ExitLoopClosure()();
            return true;
        } else if(event == Event::Return && !(childform == 4 && childbut == 1)) {
            submit->OnEvent(Event::Return);
            return true;
        }
        return false;
    });

    screen.Loop(list);
}

void LoginScreen(ftxui::ScreenInteractive& screen, std::string& next_screen) {
    using namespace ftxui;

    std::string username, password, output;
    Component user = Input(&username, "John Doe");
    InputOption passfield;
    passfield.password = true;
    Component pass = Input(&password, "admin", passfield);

    Component submit = Button("SUBMIT", [&]{
        bool f = false;
        for(const auto& i : Users) {
            if(username == i.username && password == i.password) {
                output = "Login successful";
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(3s);
                next_screen = "submit";
                screen.ExitLoopClosure()();
                f = true;
                break;
            }
        }

        if(!f) output = "Access denied. Recheck credentials.";

    }, Style());
    Component regist = Button("REGISTER", [&]{next_screen = "register"; screen.ExitLoopClosure()();}, Style());
    Component reset = Button("RESET", [&]{username = ""; password = "";}, Style());

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
                        ) | center,
                        separator(),
                        text(output) | color(output.substr(0, 6) == "Access" ? Color::Red : Color::Green)
            )
        ) | center;
    });

    screen.Loop(ui);
}

void SubmissionScreen(ftxui::ScreenInteractive& screen, std::string& next_screen) {
    using namespace ftxui;

    Component file_tree = Renderer([] {
        return window(text("Tab1 - User Explorer"), text("Lists all users"));
    });

    Component editor = Renderer([] {
        return window(text("Tab2 - Main"), text("Handling of specific tasks"));
    });

    Component chat_panel = Renderer([] {
        return window(text("Tab3 - Book Explorer"), text("Lists all books"));
    });

    Component terminal = Renderer([] {
        return window(text("Tab4 - Summary"), text("Shows summary of selected object"));
    });

    Component top_row = Container::Horizontal({
        file_tree,
        editor,
        chat_panel
    });

    Component full_layout = Container::Vertical({
        top_row,
        terminal
    });

    Component ui = Renderer([&] {
        return window(
            text("Library Management System") | underlined, vbox(
            {
                hbox({
                    file_tree->Render() | size(WIDTH, EQUAL, 30) | size(HEIGHT, EQUAL, screen.dimy() - 8),
                    editor->Render() | xflex | size(HEIGHT, EQUAL, screen.dimy() - 8),
                    chat_panel->Render() | size(WIDTH, EQUAL, 30) | size(HEIGHT, EQUAL, screen.dimy() - 8)
                }),
                terminal->Render() | size(HEIGHT, EQUAL, 8)
            }
        ));
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