#pragma once

namespace app {
namespace ios {

    struct AppDelegate : NSObject {

        static struct API {

            objc::classid cls {
                "AppDelegate","NSObject",

                objc::method {
                    "application:didFinishLaunchingWithOptions:",
                    [](AppDelegate* self,objc::selector _cmd,NSObject*) {
                        puts(_cmd.name());
                        objc::autoreleasepool autoreleasepool;
//                        UIScreen* const screen {
//                            UIScreen::mainScreen()
//                        };
//                        CADisplayLink* const displayLink {
//                            screen->displayLink(self,"updateWithDisplayLink:")
//                        };
//                        displayLink->addToRunLoop(
//                            NSRunLoop::currentRunLoop(),
//                            NSDefaultRunLoopMode
//                        );
                        auto& viewController { AppViewController::root };
                        viewController = AppViewController::alloc()->init();
                        auto& window { AppWindow::main };
                        window = AppWindow::alloc()->init();
                        window->rootViewController(viewController);
                        window->makeKeyAndVisible();
                        self->performSelectorOnMainThread("main",self,false);
                    }
                },

                objc::method {
                    "applicationDidBecomeActive:",
                    [](AppDelegate*,objc::selector _cmd,UIApplication*) {
                        puts(_cmd.name());
                        auto* const window = (app::window*)AppWindow::main;
                        window->behavior()->activated(window);
                    }
                },

                objc::method {
                    "applicationDidEnterBackground:",
                    [](AppDelegate*,objc::selector _cmd,UIApplication*) {
                        puts(_cmd.name());
                        auto* const window = (app::window*)AppWindow::main;
                        window->behavior()->deactivated(window);
                    }
                },

                objc::method {
                    "main",
                    [](AppDelegate*,objc::selector _cmd,NSObject*) {
                        puts(_cmd.name());
                        objc::autoreleasepool autoreleasepool;
                        auto* const app = UIApplication::sharedApplication();
                        app->terminate(app::main(argc,argv));
                    }
                },

                objc::method {
                    "updateWithDisplayLink:",
                    [](AppDelegate*,objc::selector _cmd,NSObject* displayLink) {
                        puts(_cmd.name());
                    }
                },
            };

            objc::message<void(SEL,NSObject*,bool)>
            performSelectorOnMainThread
            {"performSelectorOnMainThread:withObject:waitUntilDone:"};

        } api;

        static int argc;

        static char** argv;

        static
        AppDelegate*
        alloc() { return NSObject::alloc<AppDelegate>(); }

        AppDelegate*
        init() { return NSObject::init<AppDelegate>(); }

        void
        performSelectorOnMainThread(
            const objc::selector selector,
            NSObject* const arg,
            const bool wait
        ) { api.performSelectorOnMainThread(this,selector,arg,wait); }

    };

    AppDelegate::API AppDelegate::api {};

    decltype(AppDelegate::argc) AppDelegate::argc {0};

    decltype(AppDelegate::argv) AppDelegate::argv {nullptr};

}} // namespace app::ios