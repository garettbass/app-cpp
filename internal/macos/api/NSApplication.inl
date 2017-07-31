#pragma once

namespace app {
namespace macos {

    struct NSDate;
    struct NSEvent;
    struct NSMenu;
    struct NSWindow;

    //--------------------------------------------------------------------------

    using NSRunLoopMode = NSString*;

    //--------------------------------------------------------------------------

    NSRunLoopMode const NSDefaultRunLoopMode {
        (NSRunLoopMode)*CoreFoundation("NSDefaultRunLoopMode")
    };

    //--------------------------------------------------------------------------

    enum class NSApplicationActivationPolicy : NSInteger {
        Regular, 
        Accessory,
        Prohibited
    };

    //--------------------------------------------------------------------------

    struct NSApplication : NSObject {

        using ActivationPolicy = NSApplicationActivationPolicy;

        static struct API {

            objc::classid cls {"NSApplication"};

            objc::message<void(bool)>
            activate {"activateIgnoringOtherApps:"};

            objc::message<void()>
            finishLaunching {"finishLaunching"};

            objc::message<NSMenu*()>
            mainMenu {"mainMenu"};

            objc::message<NSEvent*(uintptr_t,NSDate*,NSString*,bool)>
            nextEvent {"nextEventMatchingMask:untilDate:inMode:dequeue:"};

            objc::message<void(NSEvent*)>
            sendEvent {"sendEvent:"};

            objc::message<void(ActivationPolicy)>
            setActivationPolicy {"setActivationPolicy:"};

            objc::message<void(NSObject*)>
            setDelegate {"setDelegate:"};

            objc::message<void(NSMenu*)>
            setMainMenu {"setMainMenu:"};

            objc::message<NSApplication*()>
            sharedApplication {"sharedApplication"};

            objc::message<void(NSObject*)>
            terminate {"terminate:"};

            objc::message<void()>
            updateWindows {"updateWindows"};

        } api;

        static
        NSApplication*
        sharedApplication() { return api.sharedApplication(api.cls); }

        void
        activate(bool ignoreOtherApps) {
            api.activate(this,ignoreOtherApps);
        }

        void
        finishLaunching() { api.finishLaunching(this); }

        NSMenu*
        mainMenu() { return api.mainMenu(this); }

        NSEvent*
        nextEvent(NSDate* untilDate) {
            enum { NSAnyEventMask = 0xffffffffu };
            return api.nextEvent(
                this,NSAnyEventMask,untilDate,NSDefaultRunLoopMode,true
            );
        }

        void
        sendEvent(NSEvent* event) { api.sendEvent(this,event); }

        void
        setActivationPolicy(ActivationPolicy policy) {
            api.setActivationPolicy(this,policy);
        }

        void
        setDelegate(NSObject* delegate) { api.setDelegate(this,delegate); }

        void
        setMainMenu(NSMenu* menu) { api.setMainMenu(this,menu); }

        void
        terminate() { api.terminate(this,this); }

        void
        updateWindows() { api.updateWindows(this); }

    };

    NSApplication::API NSApplication::api {};

    static NSApplication* const NSApp { NSApplication::sharedApplication() };

}} // namespace app::macos