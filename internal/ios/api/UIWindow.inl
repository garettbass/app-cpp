#pragma once

namespace app {
namespace ios {

    struct UIWindow : UIView {

        static struct API {

            objc::classid cls {"UIWindow"};

            objc::message<bool()>
            isKeyWindow {"isKeyWindow"};

            objc::message<void()>
            makeKeyAndVisible {"makeKeyAndVisible"};

            objc::message<UIViewController*()>
            rootViewController {"rootViewController"};

            objc::message<void(UIViewController*)>
            setRootViewController {"setRootViewController:"};

        } api;

        static
        UIWindow*
        alloc() { return NSObject::alloc<UIWindow>(); }

        UIWindow*
        init(CGRect frame) { return (UIWindow*)UIView::init(frame); }

        bool
        isKeyWindow() const { return api.isKeyWindow(this); }

        void
        makeKeyAndVisible() { api.makeKeyAndVisible(this); }

        UIViewController*
        rootViewController() const { return api.rootViewController(this); }

        void
        rootViewController(UIViewController* viewController) {
            api.setRootViewController(this,viewController);
        }

    };

    UIWindow::API UIWindow::api {};

}} // namespace app::ios