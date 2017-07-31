#pragma once

namespace app {
namespace macos {

    struct AppDelegate : NSObject {

        static struct API {

            objc::classid cls {
                "AppDelegate","NSObject",

                objc::method {
                    "applicationWillFinishLaunching:",
                    [](AppDelegate*, objc::selector _cmd, void* notification) {
                        puts(_cmd.name());
                        objc::autoreleasepool autoreleasepool;
                        {
                            auto* mainMenu = NSMenu::menu();
                            auto* appItem  = NSMenuItem::menuItem();
                            auto* appMenu  = NSMenu::menu();
                            auto* quitItem = NSMenuItem::menuItem(
                                NSString::string("Quit"),
                                "terminate:",
                                NSString::string("q")
                            );
                            appMenu->addItem(quitItem);
                            appItem->setSubmenu(appMenu);
                            mainMenu->addItem(appItem);
                            NSApp->setMainMenu(mainMenu);
                        }
                        NSApp->setActivationPolicy(
                            NSApplicationActivationPolicy::Regular
                        );
                    }
                },

                objc::method {
                    "applicationDidFinishLaunching:",
                    [](AppDelegate*, objc::selector _cmd, void* notification) {
                        puts(_cmd.name());
                        NSApp->activate(true);
                    }
                },

                objc::method {
                    "applicationShouldTerminate:",
                    [](AppDelegate*, objc::selector _cmd, void* application) {
                        puts(_cmd.name());
                        enum NSTerminate : uintptr_t {
                            Cancel = 0,
                            Now    = 1,
                            Later  = 2,
                        };
                        // TODO: allow app to cancel termination
                        terminated.store(true);
                        return NSTerminate::Cancel;
                    }
                },

                objc::method {
                    "applicationWillTerminate:",
                    [](AppDelegate*, objc::selector _cmd, void* notification) {
                        puts(_cmd.name());
                    }
                },
            };

        } api;

        static std::atomic<bool> terminated;

        static
        AppDelegate* alloc() { return NSObject::alloc<AppDelegate>(); }

        AppDelegate* init() { return NSObject::init<AppDelegate>(); }

    };

    AppDelegate::API AppDelegate::api {};

    decltype(AppDelegate::terminated) AppDelegate::terminated {};

}} // namespace app::macos