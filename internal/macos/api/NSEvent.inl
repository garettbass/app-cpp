#pragma once

namespace app {
namespace macos {

    struct NSWindow;

    //--------------------------------------------------------------------------

    enum class NSEventModifierFlags : NSUInteger {
        CapsLock   = 1 << 16, // Caps Lock key is pressed.
        Shift      = 1 << 17, // Shift key is pressed.
        Control    = 1 << 18, // Control key is pressed.
        Option     = 1 << 19, // Option or Alternate key is pressed.
        Command    = 1 << 20, // Command key is pressed.
        NumericPad = 1 << 21, // Any key in the numeric keypad is pressed.
        Help       = 1 << 22, // The Help key is pressed.
        Function   = 1 << 23, // Any function key is pressed.

        // Used to retrieve only the device-independent modifier flags,
        // allowing applications to mask off the device-dependent modifier
        // flags, including event coalescing information.
        DeviceIndependentFlagsMask = 0xffff0000UL
    };

    //--------------------------------------------------------------------------

    enum class NSEventType : NSUInteger {
        LeftMouseDown      = 1,
        LeftMouseUp        = 2,
        RightMouseDown     = 3,
        RightMouseUp       = 4,
        MouseMoved         = 5,
        LeftMouseDragged   = 6,
        RightMouseDragged  = 7,
        MouseEntered       = 8,
        MouseExited        = 9,
        KeyDown            = 10,
        KeyUp              = 11,
        FlagsChanged       = 12,
        AppKitDefined      = 13,
        SystemDefined      = 14,
        ApplicationDefined = 15,
        Periodic           = 16,
        CursorUpdate       = 17,
        ScrollWheel        = 22,
        TabletPoint        = 23,
        TabletProximity    = 24,
        OtherMouseDown     = 25,
        OtherMouseUp       = 26,
        OtherMouseDragged  = 27,

        Gesture            = 29,
        Magnify            = 30,
        Swipe              = 31,
        Rotate             = 18,
        BeginGesture       = 19,
        EndGesture         = 20,

        SmartMagnify       = 32,
        QuickLook          = 33,

        Pressure           = 34,
        DirectTouch        = 37,
    };

    //--------------------------------------------------------------------------

    enum class NSEventMouseButtonFlags : NSUInteger {
        Left    = 1 << 0,
        Right   = 1 << 1,
        Middle  = 1 << 2,
        Button4 = 1 << 3,
        Button5 = 1 << 4,
        Button6 = 1 << 5,
        Button7 = 1 << 6,
        Button8 = 1 << 7,
    };

    //--------------------------------------------------------------------------

    struct NSEvent : NSObject {

        static struct API {

            objc::classid cls {"NSEvent"};

            objc::message<NSPoint()>
            locationInWindow {"locationInWindow"};

            objc::message<NSEventModifierFlags()>
            modifierFlags {"modifierFlags"};

            objc::message<double()>
            timestamp {"timestamp"};

            objc::message<NSEventType()>
            type {"type"};

            objc::message<NSWindow*()>
            window {"window"};

            objc::message<NSString*()>
            characters {"characters"};

            objc::message<bool()>
            isARepeat {"isARepeat"};

            objc::message<unsigned short()>
            keyCode {"keyCode"};

            objc::message<NSEventMouseButtonFlags()>
            pressedMouseButtons {"pressedMouseButtons"};

            objc::message<NSUInteger()>
            buttonNumber {"buttonNumber"};

            objc::message<NSPoint()>
            mouseLocation {"mouseLocation"};

            objc::message<NSUInteger()>
            clickCount {"clickCount"};

            objc::message<CGFloat()>
            deltaX {"deltaX"};

            objc::message<CGFloat()>
            deltaY {"deltaY"};

            objc::message<CGFloat()>
            deltaZ {"deltaZ"};

            objc::message<CGFloat()>
            scrollingDeltaX {"scrollingDeltaX"};

            objc::message<CGFloat()>
            scrollingDeltaY {"scrollingDeltaY"};

            objc::message<bool()>
            isDirectionInvertedFromDevice {"isDirectionInvertedFromDevice"};

        } api;

        NSPoint
        locationInWindow() { return api.locationInWindow(this); }

        NSEventModifierFlags
        modifierFlags() { return api.modifierFlags(this); }

        double
        timestamp() { return api.timestamp(this); }

        NSEventType
        type() { return api.type(this); }

        NSWindow*
        window() { return api.window(this); }

        NSString*
        characters() { return api.characters(this); }

        bool
        isARepeat() { return api.isARepeat(this); }

        unsigned short
        keyCode() { return api.keyCode(this); }

        NSEventMouseButtonFlags
        pressedMouseButtons() { return api.pressedMouseButtons(this); }

        NSUInteger
        buttonNumber() { return api.buttonNumber(this); }

        NSPoint
        mouseLocation() { return api.mouseLocation(this); }

        NSUInteger
        clickCount() { return api.clickCount(this); }

        CGFloat
        deltaX() { return api.deltaX(this); }

        CGFloat
        deltaY() { return api.deltaY(this); }

        CGFloat
        deltaZ() { return api.deltaZ(this); }

        CGFloat
        scrollingDeltaX() { return api.scrollingDeltaX(this); }

        CGFloat
        scrollingDeltaY() { return api.scrollingDeltaY(this); }

        bool
        isDirectionInvertedFromDevice() {
            return api.isDirectionInvertedFromDevice(this);
        }

    };

    NSEvent::API NSEvent::api {};

}} // namespace app::macos