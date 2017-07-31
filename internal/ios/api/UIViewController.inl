#pragma once

namespace app {
namespace ios {

    struct UIViewController : UIResponder {

        static struct API {

            objc::classid cls {"UIViewController"};

            objc::message<UIView*()>
            view {"view"};

            objc::message<void(UIView*)>
            setView {"setView:"};

        } api;

        static
        UIViewController*
        alloc() { return NSObject::alloc<UIViewController>(); }

        UIViewController*
        init() { return NSObject::init<UIViewController>(); }

        UIView*
        view() { return api.view(this); }

        void
        view(UIView* view) { api.setView(this,view); }

    };

    UIViewController::API UIViewController::api {};

}} // namespace app::ios