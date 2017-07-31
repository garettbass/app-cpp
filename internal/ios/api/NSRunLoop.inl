#pragma once

namespace app {
namespace ios {

    using NSRunLoopMode = NSString*;

    //--------------------------------------------------------------------------

    NSRunLoopMode const NSDefaultRunLoopMode {
        *CoreFoundation("NSDefaultRunLoopMode")
    };

    //--------------------------------------------------------------------------

    struct NSRunLoop : NSObject {

        static struct API {

            objc::classid cls {"NSRunLoop"};

            objc::message<NSRunLoop*()>
            currentRunLoop {"currentRunLoop"};

            objc::message<NSRunLoopMode()>
            currentMode {"currentMode"};

            objc::message<NSRunLoop*()>
            mainRunLoop {"mainRunLoop"};

            objc::message<void(NSDate*)>
            runUntilDate {"runUntilDate:"};

        } api;

        static
        NSRunLoop*
        currentRunLoop() { return api.currentRunLoop(api.cls); }

        static
        NSRunLoop*
        mainRunLoop() { return api.mainRunLoop(api.cls); }

        NSRunLoopMode
        currentMode() const { return api.currentMode(this); }

        void
        run(NSDate* untilDate) { return api.runUntilDate(this,untilDate); }

    };

    NSRunLoop::API NSRunLoop::api {};

}} // namespace app::ios
