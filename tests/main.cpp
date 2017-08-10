#include <iostream>
#include "../app.inl"

int app::main(int argc, char* argv[]) {
    std::cout << "hello world\n\n";

    struct : window::delegate {
        void activated(window*) override {
            puts(__func__);
        }
        void attached(window*) override {
            puts(__func__);
        }
        void closing(window*,bool& cancel) override {
            puts(__func__);
        }
        void closed(window*) override {
            puts(__func__);
        }
        void deactivated(window*) override {
            puts(__func__);
            app::quit();
        }
        void detached(window*) override {
            puts(__func__);
        }
        void hidden(window*) override {
            puts(__func__);
        }
        void moved(window*) override {
            puts(__func__);
        }
        void resized(window*) override {
            puts(__func__);
        }
        void shown(window*) override {
            puts(__func__);
        }
    } debug_delegate;

    // auto window = app::window::main(
    auto* window = app::window::create(
        "hello world",
        &debug_delegate,
        +window::closable
        +window::minimizable
        +window::resizable
    );

    std::cout
        << "window->graphicsContext:"
        << ((app::macos::NSWindow*)window)->graphicsContext()
        << '\n';

    std::cout << app::display::primary() << '\n';

    app::activate();
    window->activate();
    // window->fillscreen();

    while (app::update(120) and !window->closed());

    delete window;

    return 0;
}