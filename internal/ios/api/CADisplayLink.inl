#pragma once

namespace app {
namespace ios {

    struct CADisplayLink : NSObject {

        static struct API {

            objc::classid cls {"CADisplayLink"};

            objc::message<void(NSRunLoop*,NSRunLoopMode)>
            addToRunLoop {"addToRunLoop:forMode:"};

            objc::message<CADisplayLink*(NSObject*,objc::selector)>
            displayLink {"displayLinkWithTarget:selector:"};

            objc::message<double()>
            duration {"duration"};

            objc::message<void()>
            invalidate {"invalidate"};

            objc::message<bool()>
            isPaused {"isPaused"};

            objc::message<NSUInteger()>
            preferredFramesPerSecond {"preferredFramesPerSecond"};

            objc::message<void(NSRunLoop*,NSRunLoopMode)>
            removeFromRunLoop {"removeFromRunLoop:forMode:"};

            objc::message<void(bool)>
            setPaused {"setPaused:"};

            objc::message<double()>
            timestamp {"timestamp"};

        } api;

        static
        CADisplayLink*
        displayLink(NSObject* target, objc::selector selector) {
            return api.displayLink(api.cls,target,selector);
        }

        void
        addToRunLoop(NSRunLoop* loop, NSRunLoopMode mode) {
            api.addToRunLoop(this,loop,mode);
        }

        double
        duration() const { return api.duration(this); }

        void
        invalidate() { api.invalidate(this); }

        bool
        paused() const { return api.isPaused(this); }

        void
        paused(bool paused) { api.setPaused(this,paused); }

        NSUInteger
        preferredFramesPerSecond() const {
            return api.preferredFramesPerSecond(this);
        }

        void
        removeFromRunLoop(NSRunLoop* loop, NSRunLoopMode mode) {
            api.removeFromRunLoop(this,loop,mode);
        }

        double
        timestamp() const { return api.timestamp(this); }

    };

    CADisplayLink::API CADisplayLink::api {};

}} // namespace app::ios