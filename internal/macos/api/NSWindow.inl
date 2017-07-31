#pragma once

namespace app {
namespace macos {

    enum class NSBackingStoreType : NSUInteger {
       Buffered = 2,
    };

    //--------------------------------------------------------------------------

    enum class NSWindowCollectionBehavior : NSUInteger {
        Default                   = 0,
        CanJoinAllSpaces          = 1 << 0,
        MoveToActiveSpace         = 1 << 1,
        Managed                   = 1 << 2,
        Transient                 = 1 << 3,
        Stationary                = 1 << 4,
        ParticipatesInCycle       = 1 << 5,
        IgnoresCycle              = 1 << 6,
        FullScreenPrimary         = 1 << 7,
        FullScreenAuxiliary       = 1 << 8,
        FullScreenNone            = 1 << 9,
        FullScreenAllowsTiling    = 1 << 11,
        FullScreenDisallowsTiling = 1 << 12,

        FullScreen = FullScreenPrimary | FullScreenAllowsTiling,
    };

    NSWindowCollectionBehavior
    operator +(NSWindowCollectionBehavior a) { return a; }

    NSWindowCollectionBehavior
    operator +(NSWindowCollectionBehavior a, NSWindowCollectionBehavior b) {
        return NSWindowCollectionBehavior(NSUInteger(a) | NSUInteger(b));
    }

    NSWindowCollectionBehavior&
    operator +=(NSWindowCollectionBehavior& a, NSWindowCollectionBehavior b) {
        return a = a + b;
    }

    NSWindowCollectionBehavior
    operator -(NSWindowCollectionBehavior a, NSWindowCollectionBehavior b) {
        return NSWindowCollectionBehavior(NSUInteger(a) & ~NSUInteger(b));
    }

    NSWindowCollectionBehavior&
    operator -=(NSWindowCollectionBehavior& a, NSWindowCollectionBehavior b) {
        return a = a - b;
    }

    bool
    operator &(NSWindowCollectionBehavior a, NSWindowCollectionBehavior b) {
        return (NSUInteger(a) & NSUInteger(b)) == NSUInteger(b);
    }

    //--------------------------------------------------------------------------

    enum class NSWindowStyleMask : NSUInteger {
       Borderless             = 0,
       Titled                 = 1 << 0,
       Closable               = 1 << 1,
       Miniaturizable         = 1 << 2,
       Resizable              = 1 << 3,
       TexturedBackground     = 1 << 8,
       UnifiedTitleAndToolbar = 1 << 12,
       FullScreen             = 1 << 14,
       FullSizeContentView    = 1 << 15,

       Default = Titled | Closable | Miniaturizable | Resizable,
    };

    NSWindowStyleMask
    operator +(NSWindowStyleMask a) { return a; }

    NSWindowStyleMask
    operator +(NSWindowStyleMask a, NSWindowStyleMask b) {
        return NSWindowStyleMask(NSUInteger(a) | NSUInteger(b));
    }

    NSWindowStyleMask&
    operator +=(NSWindowStyleMask& a, NSWindowStyleMask b) { return a = a + b; }

    NSWindowStyleMask
    operator -(NSWindowStyleMask a, NSWindowStyleMask b) {
        return NSWindowStyleMask(NSUInteger(a) & ~NSUInteger(b));
    }

    NSWindowStyleMask&
    operator -=(NSWindowStyleMask& a, NSWindowStyleMask b) { return a = a - b; }

    bool
    operator &(NSWindowStyleMask a, NSWindowStyleMask b) {
        return (NSUInteger(a) & NSUInteger(b)) == NSUInteger(b);
    }

    //--------------------------------------------------------------------------

    struct NSWindow : NSObject {

        using CollectionBehavior = NSWindowCollectionBehavior;
        using StyleMask          = NSWindowStyleMask;

        static struct API {

            objc::classid cls {"NSWindow"};

            objc::message<NSRect(NSRect,StyleMask)>
            contentRectForFrameRect
            {"contentRectForFrameRect:styleMask:"};

            objc::message<NSRect(NSRect,StyleMask)>
            frameRectForContentRect
            {"frameRectForContentRect:styleMask:"};

            objc::message<NSWindow*(NSRect,StyleMask,NSBackingStoreType,bool)>
            initWithContentRect
            {"initWithContentRect:styleMask:backing:defer:"};

            objc::message<void(bool)>
            setTitlebarAppearsTransparent
            {"setTitlebarAppearsTransparent:"};

            objc::message<void()>
            center {"center"};

            objc::message<void()>
            close {"close"};

            objc::message<CollectionBehavior()>
            collectionBehavior {"collectionBehavior"};

            objc::message<NSObject*()>
            delegate {"delegate"};

            objc::message<NSRect()>
            frame {"frame"};

            objc::message<bool()>
            isKeyWindow {"isKeyWindow"};

            objc::message<bool()>
            isMiniaturized {"isMiniaturized"};

            objc::message<bool()>
            isVisible {"isVisible"};

            objc::message<bool()>
            isZoomed {"isZoomed"};

            objc::message<void(NSObject*)>
            makeKeyAndOrderFront {"makeKeyAndOrderFront:"};

            objc::message<void(NSObject*)>
            orderFront {"orderFront:"};

            objc::message<void(NSObject*)>
            performClose {"performClose:"};

            objc::message<void(NSObject*)>
            performMiniaturize {"performMiniaturize:"};

            objc::message<void(NSObject*)>
            performZoom {"performZoom:"};

            objc::message<void(CollectionBehavior)>
            setCollectionBehavior {"setCollectionBehavior:"};

            objc::message<void(NSObject*)>
            setDelegate {"setDelegate:"};

            objc::message<void(NSRect,bool)>
            setFrame {"setFrame:display:"};

            objc::message<void(bool)>
            setIsVisible {"setIsVisible:"};

            objc::message<void(bool)>
            setReleasedWhenClosed {"setReleasedWhenClosed:"};

            objc::message<void(NSWindowStyleMask)>
            setStyleMask {"setStyleMask:"};

            objc::message<void(NSString*)>
            setTitle {"setTitle:"};

            objc::message<void(NSString*)>
            setTitleWithRepresentedFilename
            {"setTitleWithRepresentedFilename:"};

            objc::message<NSWindowStyleMask()>
            styleMask {"styleMask"};

            objc::message<NSString*()>
            title {"title"};

            objc::message<void(NSObject*)>
            toggleFullScreen {"toggleFullScreen:"};

        } api;

        static
        NSWindow*
        alloc() { return NSObject::alloc<NSWindow>(); }

        NSWindow*
        init(
            NSRect             contentRect,
            StyleMask          style,
            NSBackingStoreType backingStore,
            bool               defer
        ) {
            return api.initWithContentRect(
                this,contentRect,style,backingStore,defer
            );
        }

        static
        NSRect
        contentRectFor(NSRect frame, StyleMask style) {
            return api.contentRectForFrameRect(api.cls,frame,style);
        }

        static
        NSRect
        frameRectFor(NSRect content, StyleMask style) {
            return api.frameRectForContentRect(api.cls,content,style);
        }

        void
        center() { api.center(this); }

        void
        close() { api.close(this); }

        CollectionBehavior
        collectionBehavior() const { return api.collectionBehavior(this); }

        NSObject*
        delegate() const { return api.delegate(this); }

        NSRect
        frame() const { return api.frame(this); }

        bool
        isKeyWindow() const { return api.isKeyWindow(this); }

        bool
        isMiniaturized() const { return api.isMiniaturized(this); }

        bool
        isVisible() const { return api.isVisible(this); }

        bool
        isZoomed() const { return api.isZoomed(this); }

        void
        makeKeyAndOrderFront() { api.makeKeyAndOrderFront(this,this); }

        void
        orderFront() { api.orderFront(this,this); }

        void
        performClose() { api.performClose(this,this); }

        void
        performMiniaturize() { api.performMiniaturize(this,this); }

        void
        performZoom() { api.performZoom(this,this); }

        void
        setCollectionBehavior(CollectionBehavior collectionBehavior) {
            api.setCollectionBehavior(this,collectionBehavior);
        }

        void
        setDelegate(NSObject* delegate) { api.setDelegate(this,delegate); }

        void
        setFrame(NSRect frame, bool display = false) {
            api.setFrame(this,frame,display);
        }

        void
        setIsVisible(bool visible) { api.setIsVisible(this,visible); }

        void
        setReleasedWhenClosed(bool release) {
            api.setReleasedWhenClosed(this,release);
        }

        void
        setStyleMask(StyleMask style) { api.setStyleMask(this,style); }

        void
        setTitle(NSString* title) { api.setTitle(this,title); }

        void
        setTitleWithRepresentedFilename(NSString* title) {
            api.setTitleWithRepresentedFilename(this,title);
        }

        void
        setTitlebarAppearsTransparent(bool transparent) {
            api.setTitlebarAppearsTransparent(this,transparent);
        }

        StyleMask
        styleMask() const { return api.styleMask(this); }

        NSString*
        title() const { return api.title(this); }

        void
        toggleFullScreen() { api.toggleFullScreen(this,this); }

    };

    NSWindow::API NSWindow::api {};

}} // namespace app::macos