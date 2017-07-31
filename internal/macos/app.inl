#pragma once
#include "api/api.inl"

namespace app {

    void
    activate() {
        using namespace macos;
        objc::autoreleasepool autoreleasepool;
        NSApp->activate(true);
    }

    //--------------------------------------------------------------------------

    display
    display::primary() {
        using namespace macos;
        objc::autoreleasepool autoreleasepool;
        display primary;
        if (auto* const screen = NSScreen::mainScreen()) {
            primary.boundary = to_screen<rect>(screen->frame());
            primary.viewport = to_screen<rect>(screen->visibleFrame());
        }
        return primary;
    }

    //--------------------------------------------------------------------------

    std::vector<display>
    displays() {
        using namespace macos;
        std::vector<display> displays;
        objc::autoreleasepool autoreleasepool;
        if (auto* const array = NSScreen::screens()) {
            const size_t count = array->count();
            displays.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                auto* const screen = array->object(i);
                const rect boundary = to_screen<rect>(screen->frame());
                const rect viewport = to_screen<rect>(screen->visibleFrame());
                displays.push_back({boundary,viewport});
            }
        }
        return displays;
    }

    //--------------------------------------------------------------------------

    bool
    update(const unsigned hertz) {
        using namespace macos;
        if (not AppDelegate::terminated.load()) {
            objc::autoreleasepool autoreleasepool;
            NSDate* const timeout {
                (hertz > 0)
                ? NSDate::dateWithTimeIntervalSinceNow(1.0 / double(hertz))
                : NSDate::distantPast()
            };
            while (auto* const event = NSApp->nextEvent(timeout)) {
                NSApp->sendEvent(event);
                NSApp->updateWindows();
            }
        }
        return not AppDelegate::terminated.load();
    }

    //--------------------------------------------------------------------------

    bool
    quit() {
        using namespace macos;
        objc::autoreleasepool autoreleasepool;
        NSApp->terminate();
        return AppDelegate::terminated.load();
    }

    //--------------------------------------------------------------------------

    void
    window::operator delete(void* pointer) {
        using namespace macos;
        if (pointer != AppWindow::main) {
            ((window*)pointer)->behavior(nullptr);
            ((AppWindow*)pointer)->release();
        }
    }

    window*
    window::create() {
        using namespace macos;
        return (window*)AppWindow::alloc()->init();
    }

    window*
    window::main() {
        using namespace macos;
        static window* const main { AppWindow::main = create() };
        return main;
    }

    #define AppWindow ((AppWindow*)this)

    bool
    window::active() const {
        using namespace macos;
        return AppWindow->isKeyWindow();
    }

    void
    window::activate() {
        using namespace macos;
        AppWindow->makeKeyAndOrderFront();
    }

    window::features
    window::appearance() const {
        using namespace macos;
        const auto collectionBehavior = AppWindow->collectionBehavior();
        const auto styleMask = AppWindow->styleMask();
        features appearance { featureless };
        if (styleMask & NSWindowStyleMask::Closable) {
            appearance += closable;
        }
        if (styleMask & NSWindowStyleMask::Resizable) {
            appearance += resizable;
        }
        if (styleMask & NSWindowStyleMask::Miniaturizable) {
            appearance += minimizable;
        }
        if (collectionBehavior & NSWindowCollectionBehavior::FullScreen) {
            appearance += maximizable;
        }
        if (styleMask & NSWindowStyleMask::Titled) {
            appearance += titlebar;
        }
        return appearance;
    }

    void
    window::appearance(features appearance) {
        using namespace macos;
        auto collectionBehavior = AppWindow->collectionBehavior();
        auto styleMask {
            +NSWindowStyleMask::Titled
            +NSWindowStyleMask::FullSizeContentView
        };
        if (appearance & closable) {
            styleMask += NSWindowStyleMask::Closable;
        }
        if (appearance & resizable) {
            styleMask += NSWindowStyleMask::Resizable;
        }
        if (appearance & minimizable) {
            styleMask += NSWindowStyleMask::Miniaturizable;
        } else {
            styleMask -= NSWindowStyleMask::Miniaturizable;
        }
        if (appearance & maximizable) {
            collectionBehavior += NSWindowCollectionBehavior::FullScreen;
            collectionBehavior -= NSWindowCollectionBehavior::FullScreenNone;
        } else {
            collectionBehavior -= NSWindowCollectionBehavior::FullScreen;
            collectionBehavior += NSWindowCollectionBehavior::FullScreenNone;
        }
        if (appearance & titlebar) {
            styleMask -= NSWindowStyleMask::FullSizeContentView;
        }
        AppWindow->setTitlebarAppearsTransparent(
            styleMask & NSWindowStyleMask::FullSizeContentView
        );
        AppWindow->setStyleMask(styleMask);
        AppWindow->setCollectionBehavior(collectionBehavior);
    }

    window::delegate*
    window::behavior() const {
        using namespace macos;
        return AppWindow->behavior();
    }

    void
    window::behavior(delegate* behavior) {
        using namespace macos;
        AppWindow->behavior()->detached(this);
        AppWindow->behavior(behavior);
        AppWindow->behavior()->attached(this);
    }

    rect
    window::boundary() const {
        using namespace macos;
        return to_screen<rect>(AppWindow->frame());
    }

    void
    window::boundary(rect boundary) {
        using namespace macos;
        AppWindow->setFrame(to_screen<NSRect>(boundary),false);
    }

    rect
    window::viewport() const {
        using namespace macos;
        const auto frame = AppWindow->frame();
        const auto styleMask = AppWindow->styleMask();
        const auto content = AppWindow->contentRectFor(frame,styleMask);
        return to_screen<rect>(content);
    }

    void
    window::viewport(rect viewport) {
        using namespace macos;
        const auto content = to_screen<NSRect>(viewport);
        const auto styleMask = AppWindow->styleMask();
        const auto frame = AppWindow->frameRectFor(content,styleMask);
        AppWindow->setFrame(frame,false);
    }

    void
    window::center() {
        using namespace macos;
        AppWindow->center();
    }

    void
    window::close() {
        using namespace macos;
        AppWindow->performClose();
    }

    bool
    window::closed() const {
        using namespace macos;
        return AppWindow->closed();
    }

    bool
    window::fullscreen() const {
        using namespace macos;
        const auto styleMask = AppWindow->styleMask();
        return styleMask & NSWindowStyleMask::FullScreen;
    }

    void
    window::fullscreen(bool fullscreen) {
        using namespace macos;
        if (window::fullscreen() != fullscreen) {
            AppWindow->toggleFullScreen();
        }
    }

    bool
    window::maximized() const {
        using namespace macos;
        return AppWindow->isZoomed();
    }

    void
    window::maximized(bool maximized) {
        using namespace macos;
        if (window::maximized() != maximized) {
            AppWindow->performZoom();
        }
    }

    bool
    window::minimized() const {
        using namespace macos;
        return AppWindow->isMiniaturized();
    }

    void
    window::minimized(bool minimized) {
        using namespace macos;
        if (window::minimized() != minimized) {
            AppWindow->performMiniaturize();
        }
    }

    std::string
    window::title() const {
        using namespace macos;
        objc::autoreleasepool autoreleasepool;
        return { AppWindow->title()->UTF8String() };
    }

    void
    window::title(const std::string title) {
        using namespace macos;
        objc::autoreleasepool autoreleasepool;
        NSString* titleString = NSString::string(title.c_str());
        if (title.find('/') < title.size()) {
            AppWindow->setTitleWithRepresentedFilename(titleString);
        } else {
            AppWindow->setTitle(titleString);
        }
    }

    bool
    window::visible() const {
        using namespace macos;
        return AppWindow->isVisible();
    }

    void
    window::visible(bool visible) {
        using namespace macos;
        AppWindow->setIsVisible(visible);
    }

    #undef AppWindow

} // namespace app

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    using namespace app::macos;
    objc::autoreleasepool autoreleasepool;
    NSApp->setDelegate(AppDelegate::alloc()->init());
    NSApp->finishLaunching();
    app::update(60);
    auto* const notificationCenter = NSNotificationCenter::defaultCenter();
    notificationCenter->post(NSApplicationDidFinishLaunchingNotification,NSApp);
    const int status {app::main(argc,argv)};
    notificationCenter->post(NSApplicationWillTerminateNotification,NSApp);
    return status;
}
