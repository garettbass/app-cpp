#pragma once

namespace app {
namespace ios {

    struct CADisplayLink;

    struct UIScreen : NSObject {

        static struct API {

            objc::classid cls {"UIScreen"};

            objc::message<CADisplayLink*(NSObject*,objc::selector)>
            displayLink {"displayLinkWithTarget:selector:"};

            objc::message<CGRect()>
            bounds {"bounds"};

            objc::message<UIScreen*()>
            mainScreen {"mainScreen"};

            objc::message<CGRect()>
            nativeBounds {"nativeBounds"};

            objc::message<NSArray<UIScreen>*()>
            screens {"screens"};

        } api;

        static
        UIScreen*
        mainScreen() { return api.mainScreen(api.cls); }

        static
        NSArray<UIScreen>*
        screens() { return api.screens(api.cls); }

        CGRect
        bounds() { return api.bounds(this); }

        CADisplayLink*
        displayLink(NSObject* target, objc::selector selector) {
            return api.displayLink(this,target,selector);
        }

        CGRect
        nativeBounds() { return api.nativeBounds(this); }

    };

    UIScreen::API UIScreen::api {};

}} // namespace app::ios
