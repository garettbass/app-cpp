#pragma once

namespace app {
namespace macos {

    struct NSView : NSObject {

        static struct API {

            objc::classid cls {"NSView"};

            objc::message<void(NSView*)>
            addSubview {"addSubview:"};

            objc::message<NSRect()>
            bounds {"bounds"};

        } api;

        void
        addSubview(NSView* view) const { return api.addSubview(this,view); }

        NSRect
        bounds() const { return api.bounds(this); }

    };

    NSView::API NSView::api {};

}} // namespace app::macos