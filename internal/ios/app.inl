#pragma once
#include "api/api.inl"

namespace app {

    void
    activate() {
        // TODO?
    }

    //--------------------------------------------------------------------------

    display
    display::primary() {
        using namespace ios;
        objc::autoreleasepool autoreleasepool;
        display primary;
        if (auto* const screen = UIScreen::mainScreen()) {
            const rect bounds = to_screen<rect>(screen->bounds());
            primary.boundary = bounds;
            primary.viewport = bounds;
        }
        return primary;
    }

    //--------------------------------------------------------------------------

    std::vector<display>
    displays() {
        using namespace ios;
        std::vector<display> displays;
        objc::autoreleasepool autoreleasepool;
        if (auto* const array = UIScreen::screens()) {
            const size_t count = array->count();
            displays.reserve(count);
            for (size_t i = 0; i < count; ++i) {
                auto* const screen = array->object(i);
                const rect bounds = to_screen<rect>(screen->bounds());
                displays.push_back({bounds,bounds});
            }
        }
        return displays;
    }

    //--------------------------------------------------------------------------

    bool
    update(const unsigned hertz) {
        using namespace ios;
        objc::autoreleasepool autoreleasepool;
        NSRunLoop* const runLoop = NSRunLoop::mainRunLoop();
        NSDate* const timeout {
            (hertz > 0)
            ? NSDate::dateWithTimeIntervalSinceNow(1.0 / double(hertz))
            : NSDate::distantPast()
        };
        runLoop->run(timeout);
        return true;
    }

    //--------------------------------------------------------------------------

    bool
    quit() {
        using namespace ios;
        objc::autoreleasepool autoreleasepool;
        UIApplication::sharedApplication()->terminate(0);
        return true;
    }

    //--------------------------------------------------------------------------

    void
    window::operator delete(void* pointer) {
        using namespace ios;
        if (pointer != AppWindow::main) {
            ((window*)pointer)->behavior(nullptr);
            ((AppWindow*)pointer)->release();
        }
    }

    window*
    window::create() {
        using namespace ios;
        return (window*)AppWindow::alloc()->init();
    }

    window*
    window::main() {
        using namespace ios;
        return (window*)AppWindow::main;
    }

    #define AppWindow ((ios::AppWindow*)this)

    bool
    window::active() const {
        using namespace ios;
        return AppWindow->isKeyWindow();
    }

    void
    window::activate() {
        using namespace ios;
        AppWindow->makeKeyAndVisible();
    }

    window::features
    window::appearance() const {
        using namespace ios;
        features appearance { featureless };
        // TODO?
        return appearance;
    }

    void
    window::appearance(features appearance) {
        using namespace ios;
        // TODO?
    }

    window::delegate*
    window::behavior() const {
        using namespace ios;
        return AppWindow->behavior();
    }

    void
    window::behavior(delegate* behavior) {
        using namespace ios;
        AppWindow->behavior()->detached(this);
        AppWindow->behavior(behavior);
        AppWindow->behavior()->attached(this);
    }

    rect
    window::boundary() const {
        using namespace ios;
        return to_screen<rect>(AppWindow->bounds());
    }

    void
    window::boundary(rect boundary) {
        using namespace ios;
        AppWindow->bounds(to_screen<CGRect>(boundary));
    }

    rect
    window::viewport() const {
        using namespace ios;
        return to_screen<rect>(AppWindow->bounds());
    }

    void
    window::viewport(rect viewport) {
        using namespace ios;
        AppWindow->bounds(to_screen<CGRect>(viewport));
    }

    void
    window::center() {
        using namespace ios;
        // TODO
    }

    void
    window::close() {
        using namespace ios;
        // TODO
    }

    bool
    window::closed() const {
        using namespace ios;
        return AppWindow->closed();
    }

    bool
    window::fullscreen() const {
        using namespace ios;
        // TODO
        return true;
    }

    void
    window::fullscreen(bool fullscreen) {
        using namespace ios;
        // TODO
    }

    bool
    window::maximized() const {
        using namespace ios;
        // TODO
        return true;
    }

    void
    window::maximized(bool maximized) {
        using namespace ios;
        // TODO
    }

    bool
    window::minimized() const {
        using namespace ios;
        // TODO
        return false;
    }

    void
    window::minimized(bool minimized) {
        using namespace ios;
        // TODO
    }

    std::string
    window::title() const {
        using namespace ios;
        // TODO
        return {};
    }

    void
    window::title(const std::string title) {
        using namespace ios;
        // TODO
    }

    bool
    window::visible() const {
        using namespace ios;
        return not AppWindow->hidden();
    }

    void
    window::visible(bool visible) {
        using namespace ios;
        AppWindow->hidden(not visible);
    }

    #undef AppWindow

} // namespace app

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    using namespace app::ios;
    objc::autoreleasepool autoreleasepool;
    AppDelegate::argc = argc;
    AppDelegate::argv = argv;
    NSString* delegateName = NSString::string("AppDelegate");
    return UIApplicationMain(argc,argv,nullptr,delegateName);
}
