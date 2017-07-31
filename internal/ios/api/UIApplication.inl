#pragma once

namespace app {
namespace ios {

    struct UIEvent;

    //--------------------------------------------------------------------------

    enum class UIApplicationState : NSUInteger {
        Active,
        Inactive,
        Background,
    };

    //--------------------------------------------------------------------------

    struct UIApplication : NSObject {

        static struct API {

            objc::classid cls {"UIApplication"};

            objc::message<UIApplicationState()>
            applicationState {"applicationState"};

            objc::message<NSObject*()>
            delegate {"delegate"};

            objc::message<void(UIEvent*)>
            sendEvent {"sendEvent:"};

            objc::message<void(NSObject*)>
            setDelegate {"setDelegate:"};

            objc::message<UIApplication*()>
            sharedApplication {"sharedApplication"};

            objc::message<void(int)>
            _terminateWithStatus {"_terminateWithStatus:"};

        } api;

        static
        UIApplication*
        sharedApplication() { return api.sharedApplication(api.cls); }

        UIApplicationState
        applicationState() { return api.applicationState(this); }

        NSObject*
        delegate() const { return api.delegate(this); }

        void
        delegate(NSObject* delegate) { api.setDelegate(this,delegate); }

        void
        sendEvent(UIEvent* event) { api.sendEvent(this,event); }

        void
        terminate(int status) { api._terminateWithStatus(this,status); }

    };

    UIApplication::API UIApplication::api {};

    //--------------------------------------------------------------------------

    function_t<int(int,char**,NSString*,NSString*)>
    const UIApplicationMain = UIKit("UIApplicationMain");

}} // namespace app::ios
