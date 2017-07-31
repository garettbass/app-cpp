#pragma once
#define OBJC_NAMESPACE _app_macos_objc
#include "../../objc/objc.inl"
#undef  OBJC_NAMESPACE

namespace app {
namespace macos {

    namespace objc = _app_macos_objc;

    using objc::function_t;
    using objc::library;
    using objc::CoreFoundation;

    using objc::id;
    using objc::SEL;

    using objc::CGFloat;
    using objc::NSInteger;
    using objc::NSUInteger;

    using objc::CGPoint;
    using objc::CGSize;
    using objc::CGRect;

    using objc::NSPoint;
    using objc::NSSize;
    using objc::NSRect;

    using objc::NSObject;
    using objc::NSArray;
    using objc::NSString;

    //--------------------------------------------------------------------------

    template<typename To, typename From>
    To to(From);

    template<>
    NSPoint to(point p) {
        return {CGFloat(p.x),CGFloat(p.y)};
    }

    template<>
    point to(NSPoint n) {
        return {float(n.x),float(n.y)};
    }

    template<>
    NSSize to(size s) {
        return {CGFloat(s.w),CGFloat(s.h)};
    }

    template<>
    size to(NSSize n) {
        return {float(n.width),float(n.height)};
    }

    template<>
    NSRect to(rect r) {
        return {
            {CGFloat(r.x),CGFloat(r.y)},
            {CGFloat(r.w),CGFloat(r.h)},
        };
    }

    template<>
    rect to(NSRect n) {
        return {
            {float(n.origin.x),float(n.origin.y)},
            {float(n.size.width),float(n.size.height)},
        };
    }

    //--------------------------------------------------------------------------

    library Cocoa {"Cocoa.framework/Cocoa"};

}} // namespace app::macos

//------------------------------------------------------------------------------

#include "NSApplication.inl"
#include "NSDate.inl"
#include "NSEvent.inl"
#include "NSMenu.inl"
#include "NSMenuItem.inl"
#include "NSNotificationCenter.inl"
#include "NSScreen.inl"
#include "NSWindow.inl"

#include "AppDelegate.inl"
#include "AppWindow.inl"

//------------------------------------------------------------------------------

namespace app {
namespace macos {

    template<typename To, typename From>
    To to_screen(From);

    template<>
    NSRect to_screen(rect r) {
        objc::autoreleasepool autoreleasepool;
        auto origin_screen = NSScreen::screens()->object(0);
        auto origin_screen_height = origin_screen->frame().size.height;
        r.y = origin_screen_height - (r.y + r.h);
        return to<NSRect>(r);
    }

    template<>
    rect to_screen(NSRect n) {
        objc::autoreleasepool autoreleasepool;
        auto origin_screen = NSScreen::screens()->object(0);
        auto origin_screen_height = origin_screen->frame().size.height;
        n.origin.y = origin_screen_height - (n.origin.y + n.size.height);
        return to<rect>(n);
    }

}} // namespace app::macos