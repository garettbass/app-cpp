#pragma once

namespace app {
namespace ios {

    struct UIView : UIResponder {

        static struct API {

            objc::classid cls {"UIView"};

            objc::message<UIColor*()>
            backgroundColor {"backgroundColor"};

            objc::message<CGRect()>
            bounds {"bounds"};

            objc::message<UIView*(CGRect)>
            initWithFrame {"initWithFrame:"};

            objc::message<bool()>
            isHidden {"isHidden"};

            objc::message<void(UIColor*)>
            setBackgroundColor {"setBackgroundColor:"};

            objc::message<void(CGRect)>
            setBounds {"setBounds:"};

            objc::message<void(bool)>
            setHidden {"setHidden:"};

        } api;

        static
        UIView*
        alloc() { return NSObject::alloc<UIView>(); }

        UIView*
        init(CGRect frame) { return api.initWithFrame(this,frame); }

        UIColor*
        backgroundColor() const { return api.backgroundColor(this); }

        void
        backgroundColor(UIColor* color) {
            api.setBackgroundColor(this,color);
        }

        CGRect
        bounds() const { return api.bounds(this); }

        void
        bounds(CGRect bounds) { api.setBounds(this,bounds); }

        bool
        hidden() const { return api.isHidden(this); }

        void
        hidden(bool hidden) { api.setHidden(this,hidden); }

    };

    UIView::API UIView::api {};

}} // namespace app::ios
