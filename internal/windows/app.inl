#pragma once
#include "api/api.inl"

namespace app {

    void
    activate() {
        using namespace windows;
        if (HWND hwnd {GetActiveWindow()}) {
            SetForegroundWindow(hwnd);
        }
    }

    //--------------------------------------------------------------------------

    display
    display::primary() {
        using namespace windows;
        display primary;
        auto const hmon = MonitorFromPoint({0,0},MONITOR_DEFAULT::PRIMARY);
        MONITORINFO mi;
        if (GetMonitorInfoA(hmon,mi)) {
            primary = to<display>(mi);
        }
        return primary;
    }

    //--------------------------------------------------------------------------

    std::vector<display>
    displays() {
        using namespace windows;
        std::vector<display> displays;
        struct local {
            static
            BOOL __stdcall
            MonitorEnumProc(HMONITOR hmon,HDC,LPRECT rect,LPVOID lparam) {
                MONITORINFO mi;
                if (GetMonitorInfoA(hmon,mi)) {
                    auto& displays = (std::vector<display>&)lparam;
                    displays.push_back(to<display>(mi));
                }
                return true;
            };
        };
        EnumDisplayMonitors(nullptr,nullptr,local::MonitorEnumProc,&displays);
        return displays;
    }

    //--------------------------------------------------------------------------

    bool
    update(const unsigned hertz) {
        using namespace windows;
        MSG msg;
        while (PeekMessageA(msg,nullptr,WM::NONE,WM::NONE,PM::REMOVE)) {
            TranslateMessage(msg);
            DispatchMessageA(msg);
        }
        return true; // TODO: return false after WM::QUIT
    }

    //--------------------------------------------------------------------------

    bool
    quit() {
        using namespace windows;
        // SendMessageA(hwnd,WM::QUIT,0,0);
        return true; // TODO: enable cancellation
    }

    //--------------------------------------------------------------------------

    void
    window::operator delete(void* pointer) {
        using namespace windows;
        if (pointer != AppWindow::main) {
            ((window*)pointer)->behavior(nullptr);
            DestroyWindow(HWND(pointer));
        }
    }

    window*
    window::create() {
        using namespace windows;
        HWND const hwnd {
            CreateWindowExA(
                +WS_EX::NONE,
                LPCSTR(AppWindow::atom),
                nullptr,
                +WS::OVERLAPPEDWINDOW
                +WS::CLIPSIBLINGS
                +WS::CLIPCHILDREN,
                0,0,800,600,
                nullptr,
                nullptr,
                HINSTANCE(GetModuleHandleA(nullptr)),
                nullptr
            )
        };
        auto* const window = (app::window*)hwnd;
        window->boundary(display::primary().viewport / 2);
        window->center();
        return window;
    }

    window*
    window::main() {
        using namespace windows;
        static window* const main { AppWindow::main = create() };
        return main;
    }

    #define hwnd (HWND(this))

    bool
    window::active() const {
        using namespace windows;
        return (GetActiveWindow() == hwnd);
    }

    void
    window::activate() {
        using namespace windows;
        if (not IsWindowVisible(hwnd)) {
            ShowWindow(hwnd,SW::SHOWNOACTIVATE);
        }
        SetActiveWindow(hwnd);
    }

    window::features
    window::appearance() const {
        using namespace windows;
        // TODO
        // https://www.codeproject.com/Articles/32623/Vista-Aero-ToolStrip-on-Non-Client-Area
        // https://msdn.microsoft.com/en-us/library/windows/desktop/bb688195(v=vs.85).aspx
        // https://codexample.org/questions/262752/how-to-glow-the-minimum-maximum-and-close-button.c
        return window::featureless;
    }

    void
    window::appearance(features appearance) {
        using namespace windows;
        // TODO
    }

    window::delegate*
    window::behavior() const {
        using namespace windows;
        auto const behavior = AppWindow::GetBehavior(hwnd);
        return behavior ? behavior : app::window::delegate::null;
    }

    void
    window::behavior(delegate* behavior) {
        using namespace windows;
        window::behavior()->detached(this);
        AppWindow::SetBehavior(hwnd,behavior);
        window::behavior()->attached(this);
    }

    rect
    window::boundary() const {
        using namespace windows;
        RECT rc; GetWindowRect(hwnd,rc);
        return to<rect>(rc);
    }

    void
    window::boundary(rect boundary) {
        using namespace windows;
        WINDOWPLACEMENT wpl;
        GetWindowPlacement(hwnd,wpl);
        wpl.rcNormalPosition = to<RECT>(boundary);
        SetWindowPlacement(hwnd,wpl);
    }

    rect
    window::viewport() const {
        using namespace windows;
        RECT rc; GetClientRect(hwnd,rc);
        return to<rect>(rc);
    }

    void
    window::viewport(rect viewport) {
        using namespace windows;
        const auto style = WS(GetWindowLongPtrA(hwnd,int(GWLP::STYLE)));
        const auto exstyle = WS_EX(GetWindowLongPtrA(hwnd,int(GWLP::EXSTYLE)));
        RECT rc = to<RECT>(viewport);
        AdjustWindowRectEx(rc,style,false,exstyle);
        WINDOWPLACEMENT wpl;
        GetWindowPlacement(hwnd,wpl);
        wpl.rcNormalPosition = rc;
        SetWindowPlacement(hwnd,wpl);
    }

    void
    window::center() {
        using namespace windows;
        RECT rc; GetWindowRect(hwnd,rc);
        HMONITOR hmon {MonitorFromRect(rc,MONITOR_DEFAULT::PRIMARY)};
        MONITORINFO mi; GetMonitorInfoA(hmon,mi);
        const rect desktop {to<rect>(mi.rcWork)};
        rect window {to<rect>(rc)};
        if (window.w > desktop.w) window.w = desktop.w;
        if (window.h > desktop.h) window.h = desktop.h;
        const float dw = desktop.w - window.w;
        const float dh = desktop.h - window.h;
        window.x = dw / 2;
        window.y = dh / 3;
        boundary(window);
    }

    void
    window::close() {
        using namespace windows;
        SendMessageA(hwnd,WM::CLOSE,0,0);
    }

    bool
    window::closed() const {
        using namespace windows;
        return AppWindow::GetClosed(hwnd);
    }

    bool
    window::fullscreen() const {
        using namespace windows;
        return AppWindow::GetFullscreen(hwnd);
    }

    void
    window::fullscreen(bool fullscreen) {
        using namespace windows;
        if (window::fullscreen() != fullscreen) {
            if (fullscreen) {
                RECT rc; GetWindowRect(hwnd,rc);
                HMONITOR hmon {MonitorFromRect(rc,MONITOR_DEFAULT::PRIMARY)};
                MONITORINFO mi; GetMonitorInfoA(hmon,mi);
                WINDOWPLACEMENT wpl; GetWindowPlacement(hwnd,wpl);

                AppWindow::SetFullscreen(hwnd,true);
                AppWindow::SetRestoreAppearance(hwnd,appearance());
                AppWindow::SetRestoreShowCmd(hwnd,wpl.showCmd);
                AppWindow::SetRestoreRect(hwnd,wpl.rcNormalPosition);

                const WS style {WS::CLIPCHILDREN+WS::CLIPSIBLINGS+WS::VISIBLE};
                AppWindow::SetStyle(hwnd,style);
                rc = mi.rcMonitor;
                SetWindowPos(
                    hwnd,HWND_TOP,
                    rc.left, rc.top,
                    rc.right-rc.left,
                    rc.bottom-rc.top,
                    +SWP::NOOWNERZORDER
                    +SWP::FRAMECHANGED
                );
            } else {
                AppWindow::SetFullscreen(hwnd,false);
                WINDOWPLACEMENT wpl; GetWindowPlacement(hwnd,wpl);
                wpl.showCmd = AppWindow::GetRestoreShowCmd(hwnd);
                wpl.rcNormalPosition = AppWindow::GetRestoreRect(hwnd);
                SetWindowPlacement(hwnd,wpl);
                appearance(AppWindow::GetRestoreAppearance(hwnd));
            }
        }
    }

    bool
    window::maximized() const {
        using namespace windows;
        return bool(IsZoomed(hwnd));
    }

    void
    window::maximized(bool maximized) {
        using namespace windows;
        if (window::maximized() != maximized) {
            if (maximized) {
                ShowWindow(hwnd,SW::SHOWMAXIMIZED);
            } else {
                ShowWindow(hwnd,SW::RESTORE);
            }
        }
    }

    bool
    window::minimized() const {
        using namespace windows;
        return bool(IsIconic(hwnd));
    }

    void
    window::minimized(bool minimized) {
        using namespace windows;
        if (window::minimized() != minimized) {
            if (minimized) {
                ShowWindow(hwnd,SW::SHOWMINIMIZED);
            } else {
                ShowWindow(hwnd,SW::RESTORE);
            }
        }
    }

    std::string
    window::title() const {
        using namespace windows;
        const int length {GetWindowTextLengthA(hwnd)};
        std::string title(size_t(length),'\0');
        GetWindowTextA(hwnd,&title.front(),length + 1);
        return title;
    }

    void
    window::title(const std::string title) {
        using namespace windows;
        SetWindowTextA(hwnd,title.c_str());
    }

    bool
    window::visible() const {
        using namespace windows;
        return bool(IsWindowVisible(hwnd));
    }

    void
    window::visible(bool visible) {
        using namespace windows;
        if (window::visible() != visible) {
            if (visible) {
                ShowWindow(hwnd,SW::RESTORE);
            } else {
                ShowWindow(hwnd,SW::HIDE);
            }
        }
    }

    #undef hwnd

} // namespace app

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
    using namespace app::windows;
    SetProcessDpiAwareness(PROCESS_DPI_AWARENESS::MONITOR_DPI_AWARE);
    const int status {app::main(argc,argv)};
    return status;
}
