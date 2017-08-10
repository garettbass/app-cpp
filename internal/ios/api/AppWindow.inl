#pragma once

namespace app {
namespace ios {

    //--------------------------------------------------------------------------

    struct AppWindow : UIWindow {

        using behavior_t = app::window::delegate*;

        static struct API {

            objc::classid cls {
                "AppWindow","UIWindow",

                objc::variable<behavior_t>{"behavior"},

                objc::variable<bool>{"closed"},
            };

            objc::accessor<behavior_t>
            behavior {cls,"behavior"};

            objc::accessor<bool>
            closed {cls,"closed"};

        } api;

        static AppWindow* main;

        static
        AppWindow*
        newWindow() {
            objc::autoreleasepool autoreleasepool;
            UIScreen* const screen { UIScreen::mainScreen() };
            AppWindow* const window { alloc<AppWindow>() };
            window->init(screen->bounds());
            window->backgroundColor(UIColor::redColor());
            return window;
        }

        behavior_t
        behavior() const {
            auto behavior = api.behavior(this);
            return behavior ? behavior : window::delegate::null;
        }

        void
        behavior(behavior_t behavior) { api.behavior(this) = behavior; }

        bool
        closed() const { return api.closed(this); }

        void
        closed(bool closed) { api.closed(this) = closed; }

    };

    AppWindow::API AppWindow::api {};

    decltype(AppWindow::main) AppWindow::main { nullptr };

}} // namespace app::ios