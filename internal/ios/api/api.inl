#pragma once
#define OBJC_NAMESPACE _app_ios_objc
#include "../../objc/objc.inl"
#undef  OBJC_NAMESPACE

namespace app {
namespace ios {

    namespace objc = _app_ios_objc;

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
    point to(NSPoint p) {
        return {float(p.x),float(p.y)};
    }

    template<>
    NSSize to(size s) {
        return {CGFloat(s.w),CGFloat(s.h)};
    }

    template<>
    size to(NSSize s) {
        return {float(s.width),float(s.height)};
    }

    template<>
    NSRect to(rect r) {
        return {
            {CGFloat(r.x),CGFloat(r.y)},
            {CGFloat(r.w),CGFloat(r.h)},
        };
    }

    template<>
    rect to(NSRect r) {
        return {
            {float(r.origin.x),float(r.origin.y)},
            {float(r.size.width),float(r.size.height)},
        };
    }

    //--------------------------------------------------------------------------

    library UIKit {"UIKit.framework/UIKit"};

}} // namespace app::ios

#include "NSDate.inl"
#include "NSRunLoop.inl"

#include "UIApplication.inl"
#include "UIColor.inl"
#include "UIResponder.inl"
#include "UIScreen.inl"
#include "UIView.inl"
#include "UIViewController.inl"
#include "UIWindow.inl"

#include "CADisplayLink.inl"

#include "AppViewController.inl"
#include "AppWindow.inl"
#include "AppDelegate.inl"

//------------------------------------------------------------------------------

namespace app {
namespace ios {

    template<typename To, typename From>
    To to_screen(From);

    template<>
    NSRect to_screen(rect r) { return to<NSRect>(r); }

    template<>
    rect to_screen(NSRect n) { return to<rect>(n); }

}} // namespace app::ios
