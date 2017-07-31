#pragma once
#include <cassert>
#include <iostream>
#include "app.hpp"

//------------------------------------------------------------------------------

namespace app {

    int main(int argc, char* argv[]);

    //--------------------------------------------------------------------------

    void window::fillscreen() { fullscreen(true); }

    bool window::hidden() const      { return !visible(); }
    void window::hidden(bool hidden) { visible(!hidden); }
    void window::hide()              { hidden(true); }

    void window::maximize() { maximized(true); }

    void window::minimize() { minimized(true); }

    void
    window::restore() {
        if (fullscreen()) return fullscreen(false);
        if (maximized())  return maximized(false);
        if (minimized())  return minimized(false);
        if (hidden())     return hidden(false);
    }

    void window::show() { visible(true); }

    //--------------------------------------------------------------------------

    static window::delegate window__delegate__null {};

    decltype(window::delegate::null)
    window::delegate::null { &window__delegate__null };

} // namespace app

//------------------------------------------------------------------------------

std::ostream& operator <<(std::ostream& out, const app::point& p) {
    return out<<"{x:"<<p.x<<",y:"<<p.y<<'}';
}

std::ostream& operator <<(std::ostream& out, const app::size& s) {
    return out<<"{w:"<<s.w<<",h:"<<s.h<<'}';
}

std::ostream& operator <<(std::ostream& out, const app::rect& r) {
    return out<<"{x:"<<r.x<<",y:"<<r.y<<",w:"<<r.w<<",h:"<<r.h<<'}';
}

std::ostream& operator <<(std::ostream& out, const app::display& d) {
    return out
        <<'{'
        <<"boundary:"<<d.boundary<<','
        <<"viewport:"<<d.viewport
        <<'}';
}

//------------------------------------------------------------------------------

#include "internal/cxx/push.h"
#include "internal/cxx/cxx.h"
#if CXX_OS_IOS

    #include "internal/ios/app.inl"

#elif CXX_OS_MACOS

    #include "internal/macos/app.inl"

#elif CXX_OS_WINDOWS

    #include "internal/windows/app.inl"

#else // CXX_OS_?

    #error "unsupported platform"

#endif // CXX_OS_*
#include "internal/cxx/pop.h"
