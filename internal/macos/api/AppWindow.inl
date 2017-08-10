#pragma once

namespace app {
namespace macos {

    struct AppView : NSView {

        static struct API {

            objc::classid cls {
                "AppView","NSView",

                objc::method{
                    "isFlipped",
                    [](AppView* self,objc::selector){
                        return true;
                    }
                },
            };

        } api;

        static
        AppView*
        newView() { return alloc<AppView>()->init<AppView>(); }

    };

    AppView::API AppView::api;

    //--------------------------------------------------------------------------

    struct AppWindow : NSWindow {

        using behavior_t = app::window::delegate*;

        static struct API {

            objc::classid cls {
                "AppWindow","NSWindow",

                objc::variable<behavior_t>{"behavior"},

                objc::variable<bool>{"closed"},

                // objc::method {"retain",[](id self, objc::selector _cmd){
                //     self = objc::message<id()>{_cmd}(objc::super(self));
                //     std::cout << "AppWindow::retain(): " << objc::get_retain_count(self) << '\n';
                //     return self;
                // }},

                // objc::method {"release",[](id self, objc::selector _cmd){
                //     objc::message<void()>{_cmd}(objc::super(self));
                //     std::cout << "AppWindow::retain(): " << objc::get_retain_count(self) << '\n';
                // }},

                objc::method{
                    "windowShouldClose:",
                    [](AppWindow* self,objc::selector,void*){
                        bool cancel = false;
                        self->behavior()->closing((app::window*)self,cancel);
                        return not cancel;
                    }
                },

                objc::method{
                    "windowWillClose:",
                    [](AppWindow* self,objc::selector,void*){
                        self->closed(true);
                        self->behavior()->closed((app::window*)self);
                    }
                },

                objc::method{
                    "windowDidChangeOcclusionState:",
                    [](AppWindow* self,objc::selector,void*){
                        if (self->isVisible()) {
                            self->closed(false);
                            self->behavior()->shown((app::window*)self);
                        } else {
                            self->behavior()->hidden((app::window*)self);
                        }
                    }
                },

                objc::method{
                    "windowDidMove:",
                    [](AppWindow* self,objc::selector,void*){
                        self->behavior()->moved((app::window*)self);
                    }
                },

                objc::method{
                    "windowDidResize:",
                    [](AppWindow* self,objc::selector,void*){
                        self->behavior()->resized((app::window*)self);
                    }
                },
            };

            objc::accessor<behavior_t>
            behavior {cls,"behavior"};

            objc::accessor<bool>
            closed {cls,"closed"};

            objc::property<readwrite,NSView*>
            contentView {"contentView","setContentView:"};

        } api;

        static app::window* main;

        static
        AppWindow*
        newWindow() {
            objc::autoreleasepool autoreleasepool;
            NSRect contentRect { NSScreen::mainScreen()->visibleFrame() };
            contentRect.size.width /= 2;
            contentRect.size.height /= 2;
            AppWindow* const window { alloc<AppWindow>() };
            window->init(contentRect);
            window->contentView(AppView::newView());
            window->center();
            window->setReleasedWhenClosed(false);
            window->setDelegate(window);
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

        NSView*
        contentView() const { return api.contentView(this); }

        void
        contentView(NSView* view) { api.contentView(this,view); }

    };

    AppWindow::API AppWindow::api {};

    decltype(AppWindow::main) AppWindow::main { nullptr };

}} // namespace app::macos