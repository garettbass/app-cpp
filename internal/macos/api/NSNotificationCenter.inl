#pragma once

namespace app {
namespace macos {

    NSString* const NSApplicationDidFinishLaunchingNotification {
        *Cocoa("NSApplicationDidFinishLaunchingNotification")
    };

    NSString* const NSApplicationWillTerminateNotification {
        *Cocoa("NSApplicationWillTerminateNotification")
    };

    //--------------------------------------------------------------------------

    struct NSNotificationCenter : NSObject {

        static struct API {

            objc::classid cls {"NSNotificationCenter"};

            objc::message<NSNotificationCenter*()>
            defaultCenter {"defaultCenter"};

            objc::message<void(NSString*,NSObject*)>
            postNotification {"postNotificationName:object:"};

        } api;

        static
        NSNotificationCenter*
        defaultCenter() { return api.defaultCenter(api.cls); }

        void
        post(NSString* name, NSObject* object) {
            api.postNotification(this,name,object);
        }

    };

    NSNotificationCenter::API NSNotificationCenter::api {};

}} // namespace app::macos
