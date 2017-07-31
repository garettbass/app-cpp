#pragma once

namespace app {
namespace macos {

    struct NSScreen : NSObject {

        static struct API {

            objc::classid cls {"NSScreen"};

            objc::message<NSRect()>
            frame {"frame"};

            objc::message<NSScreen*()>
            mainScreen {"mainScreen"};

            objc::message<NSArray<NSScreen>*()>
            screens {"screens"};

            objc::message<NSRect()>
            visibleFrame {"visibleFrame"};

        } api;

        static
        NSScreen*
        mainScreen() { return api.mainScreen(api.cls); }

        static
        NSArray<NSScreen>*
        screens() { return api.screens(api.cls); }

        NSRect
        frame() const { return api.frame(this); }

        NSRect
        visibleFrame() const { return api.visibleFrame(this); }

    };

    NSScreen::API NSScreen::api {};

}} // namespace app::macos