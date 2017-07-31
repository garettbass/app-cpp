#pragma once

namespace app {
namespace ios {

    struct AppViewController : UIViewController {

        static struct API {

            objc::classid cls {
                "AppViewController","UIViewController",

                objc::method{
                    "loadView",
                    [](AppViewController* self,objc::selector _cmd) {
                        puts(_cmd.name());
                        objc::autoreleasepool autoreleasepool;
                        UIScreen* const screen {
                            UIScreen::mainScreen()
                        };
                        self->view(UIView::alloc()->init(screen->bounds()));
                    }
                },

                objc::method{
                    "viewDidLoad",
                    [](AppViewController* self,objc::selector _cmd) {
                        puts(_cmd.name());
                    }
                },

                objc::method{
                    "didReceiveMemoryWarning",
                    [](AppViewController* self,objc::selector _cmd) {
                        puts(_cmd.name());
                    }
                },

                objc::method{
                    "touchesBegan:withEvent:",
                    [](AppViewController* self,objc::selector _cmd,id,id) {
                        puts(_cmd.name());
                    }
                }
            };

        } api;

        static AppViewController* root;

        static
        AppViewController*
        alloc() { return NSObject::alloc<AppViewController>(); }

        AppViewController*
        init() { return NSObject::init<AppViewController>(); }

    };

    AppViewController::API AppViewController::api {};

    decltype(AppViewController::root) AppViewController::root { nullptr };

}} // namespace app::ios
