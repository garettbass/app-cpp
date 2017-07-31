#pragma once
#include "library.inl"

#define WINAPI __stdcall

#define DLLAPI(Library,Result,Name,Parameters) \
        Result (WINAPI * const Name) Parameters { Library.function(#Name) }

namespace app {
namespace windows {

    using ATOM      = uint16_t;
    using BYTE      = uint8_t;
    using BOOL      = int32_t;
    using UINT      = uint32_t;
    using LPSTR     = char*;
    using LPCSTR    = const char*;
    using WORD      = uint16_t;
    using DWORD     = uint32_t;
    using LONG      = uint32_t;
    using LONGLONG  = uint64_t;
    using DWORD_PTR = uintptr_t;
    using INT_PTR   = intptr_t;
    using LONG_PTR  = intptr_t;
    using UINT_PTR  = uintptr_t;
    using HRESULT   = uint32_t;

    using FARPROC   = void*;
    using HMODULE   = struct MODULE*;

    using LRESULT   = LONG_PTR;
    using LPVOID    = void*;

    using HDC       = struct DC*;
    using HMENU     = struct MENU*;
    using HICON     = struct ICON*;
    using HBRUSH    = struct BRUSH*;
    using HCURSOR   = struct CURSOR*;
    using HGDIOBJ   = struct GDIOBJ*;
    using HINSTANCE = struct INSTANCE*;
    using HMONITOR  = struct MONITOR*;

    //--------------------------------------------------------------------------

    using HWND      = struct WND*;

    HWND const HWND_BOTTOM    = HWND( 1);
    HWND const HWND_NOTOPMOST = HWND(-2);
    HWND const HWND_TOP       = HWND( 0);
    HWND const HWND_TOPMOST   = HWND(-1);

    //--------------------------------------------------------------------------

    struct POINT { LONG x, y; };
    using PPOINT = POINT*;

    struct RECT {
        LONG left, top, right, bottom;
        LONG width()  const { return right - left; }
        LONG height() const { return bottom - top; }
    };
    using LPRECT = RECT*;
    using LPCRECT = const LPRECT;

    //--------------------------------------------------------------------------

    enum class CS : UINT {
        NONE            = 0,
        VREDRAW         = 0x00000001,
        HREDRAW         = 0x00000002,
        DBLCLKS         = 0x00000008,
        OWNDC           = 0x00000020,
        CLASSDC         = 0x00000040,
        PARENTDC        = 0x00000080,
        NOCLOSE         = 0x00000200,
        SAVEBITS        = 0x00000800,
        BYTEALIGNCLIENT = 0x00001000,
        BYTEALIGNWINDOW = 0x00002000,
        GLOBALCLASS     = 0x00004000,
        DROPSHADOW      = 0x00020000,
    };

    CS   operator + (CS a)        { return a; }
    CS   operator + (CS a, CS b)  { return CS(UINT(a) | UINT(b)); }
    CS&  operator +=(CS& a, CS b) { return a = a + b; }
    CS   operator - (CS a, CS b)  { return CS(UINT(a) & ~UINT(b)); }
    CS&  operator -=(CS& a, CS b) { return a = a - b; }
    bool operator & (CS a, CS b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class CLR : int {
        ACTIVEBORDER            = 10,
        ACTIVECAPTION           = 2,
        APPWORKSPACE            = 12,
        BACKGROUND              = 1,
        BTNFACE                 = 15,
        BTNHIGHLIGHT            = 20,
        BTNSHADOW               = 16,
        BTNTEXT                 = 18,
        CAPTIONTEXT             = 9,
        DESKTOP                 = 1,
        DKSHADOW_3D             = 21,
        FACE_3D                 = 15,
        GRADIENTACTIVECAPTION   = 27,
        GRADIENTINACTIVECAPTION = 28,
        GRAYTEXT                = 17,
        HIGHLIGHT               = 13,
        HIGHLIGHT_3D            = 20,
        HIGHLIGHTTEXT           = 14,
        HOTLIGHT                = 26,
        INACTIVEBORDER          = 11,
        INACTIVECAPTION         = 3,
        INACTIVECAPTIONTEXT     = 19,
        INFOBK                  = 24,
        INFOTEXT                = 23,
        LIGHT_3D                = 22,
        MENU                    = 4,
        MENUBAR                 = 30,
        MENUHILIGHT             = 29,
        MENUTEXT                = 7,
        SCROLLBAR               = 0,
        SHADOW_3D               = 16,
        WINDOW                  = 5,
        WINDOWFRAME             = 6,
        WINDOWTEXT              = 8,
    };

    CLR  operator + (CLR a)         { return a; }
    CLR  operator + (CLR a, CLR b)  { return CLR(UINT(a) | UINT(b)); }
    CLR& operator +=(CLR& a, CLR b) { return a = a + b; }
    CLR  operator - (CLR a, CLR b)  { return CLR(UINT(a) & ~UINT(b)); }
    CLR& operator -=(CLR& a, CLR b) { return a = a - b; }
    bool operator & (CLR a, CLR b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class IDC : UINT_PTR {
        APPSTARTING = 32650,
        ARROW       = 32512,
        CROSS       = 32515,
        HAND        = 32649,
        HELP        = 32651,
        IBEAM       = 32513,
        ICON        = 32641,
        NO          = 32648,
        SIZE        = 32640,
        SIZEALL     = 32646,
        SIZENESW    = 32643,
        SIZENS      = 32645,
        SIZENWSE    = 32642,
        SIZEWE      = 32644,
        UPARROW     = 32516,
        WAIT        = 32514,
    };

    //--------------------------------------------------------------------------

    enum class PDA {
        UNAWARE           = 0,
        SYSTEM_DPI_AWARE  = 1,
        MONITOR_DPI_AWARE = 2,
    };
    using PROCESS_DPI_AWARENESS = PDA;

    //--------------------------------------------------------------------------

    enum class WS : UINT {
        NONE             = 0L,
        BORDER           = 0x00800000L,
        CAPTION          = 0x00C00000L,
        CHILD            = 0x40000000L,
        CHILDWINDOW      = 0x40000000L,
        CLIPCHILDREN     = 0x02000000L,
        CLIPSIBLINGS     = 0x04000000L,
        DISABLED         = 0x08000000L,
        DLGFRAME         = 0x00400000L,
        GROUP            = 0x00020000L,
        HSCROLL          = 0x00100000L,
        ICONIC           = 0x20000000L,
        MAXIMIZE         = 0x01000000L,
        MAXIMIZEBOX      = 0x00010000L,
        MINIMIZE         = 0x20000000L,
        MINIMIZEBOX      = 0x00020000L,
        OVERLAPPED       = 0x00000000L,
        POPUP            = 0x80000000L,
        SIZEBOX          = 0x00040000L,
        SYSMENU          = 0x00080000L,
        TABSTOP          = 0x00010000L,
        THICKFRAME       = 0x00040000L,
        TILED            = 0x00000000L,
        VISIBLE          = 0x10000000L,
        VSCROLL          = 0x00200000L,
        OVERLAPPEDWINDOW = CAPTION
                         | SYSMENU
                         | THICKFRAME
                         | MINIMIZEBOX
                         | MAXIMIZEBOX,
        POPUPWINDOW      = POPUP
                         | BORDER
                         | SYSMENU,
        TILEDWINDOW      = CAPTION
                         | SYSMENU
                         | THICKFRAME
                         | MINIMIZEBOX
                         | MAXIMIZEBOX,
    };

    WS   operator + (WS a)        { return a; }
    WS   operator + (WS a, WS b)  { return WS(UINT(a) | UINT(b)); }
    WS&  operator +=(WS& a, WS b) { return a = a + b; }
    WS   operator - (WS a, WS b)  { return WS(UINT(a) & ~UINT(b)); }
    WS&  operator -=(WS& a, WS b) { return a = a - b; }
    bool operator & (WS a, WS b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class WSX : UINT {
        NONE                = 0L,
        ACCEPTFILES         = 0x00000010L,
        APPWINDOW           = 0x00040000L,
        CLIENTEDGE          = 0x00000200L,
        COMPOSITED          = 0x02000000L,
        CONTEXTHELP         = 0x00000400L,
        CONTROLPARENT       = 0x00010000L,
        DLGMODALFRAME       = 0x00000001L,
        LAYERED             = 0x00080000,
        LAYOUTRTL           = 0x00400000L,
        LEFT                = 0x00000000L,
        LEFTSCROLLBAR       = 0x00004000L,
        LTRREADING          = 0x00000000L,
        MDICHILD            = 0x00000040L,
        NOACTIVATE          = 0x08000000L,
        NOINHERITLAYOUT     = 0x00100000L,
        NOPARENTNOTIFY      = 0x00000004L,
        NOREDIRECTIONBITMAP = 0x00200000L,
        RIGHT               = 0x00001000L,
        RIGHTSCROLLBAR      = 0x00000000L,
        RTLREADING          = 0x00002000L,
        STATICEDGE          = 0x00020000L,
        TOOLWINDOW          = 0x00000080L,
        TOPMOST             = 0x00000008L,
        TRANSPARENT         = 0x00000020L,
        WINDOWEDGE          = 0x00000100L,
        OVERLAPPEDWINDOW    = WINDOWEDGE | CLIENTEDGE,
        PALETTEWINDOW       = WINDOWEDGE | TOOLWINDOW | TOPMOST,
    };
    using WS_EX = WSX;

    WSX  operator + (WSX a)         { return a; }
    WSX  operator + (WSX a, WSX b)  { return WSX(UINT(a) | UINT(b)); }
    WSX& operator +=(WSX& a, WSX b) { return a = a + b; }
    WSX  operator - (WSX a, WSX b)  { return WSX(UINT(a) & ~UINT(b)); }
    WSX& operator -=(WSX& a, WSX b) { return a = a - b; }
    bool operator & (WSX a, WSX b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class WPF : UINT {
        NONE                 = 0x0000,
        SETMINPOSITION       = 0x0001,
        RESTORETOMAXIMIZED   = 0x0002,
        ASYNCWINDOWPLACEMENT = 0x0004,
    };

    WPF  operator + (WPF a)         { return a; }
    WPF  operator + (WPF a, WPF b)  { return WPF(UINT(a) | UINT(b)); }
    WPF& operator +=(WPF& a, WPF b) { return a = a + b; }
    WPF  operator - (WPF a, WPF b)  { return WPF(UINT(a) & ~UINT(b)); }
    WPF& operator -=(WPF& a, WPF b) { return a = a - b; }
    bool operator & (WPF a, WPF b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class GWLP : int {
        EXSTYLE   = -20,
        HINSTANCE =  -6,
        ID        = -12,
        STYLE     = -16,
        USERDATA  = -21,
        WNDPROC   =  -4,
    };

    //--------------------------------------------------------------------------

    enum class MIF : UINT {
        NONE    = 0,
        PRIMARY = 0x00000001,
    };
    using MONITORINFOF = MIF;

    MIF  operator + (MIF a)         { return a; }
    MIF  operator + (MIF a, MIF b)  { return MIF(UINT(a) | UINT(b)); }
    MIF& operator +=(MIF& a, MIF b) { return a = a + b; }
    MIF  operator - (MIF a, MIF b)  { return MIF(UINT(a) & ~UINT(b)); }
    MIF& operator -=(MIF& a, MIF b) { return a = a - b; }
    bool operator & (MIF a, MIF b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class MD : UINT {
        NONE    = 0,
        PRIMARY = 0x00000001,
        NEAREST = 0x00000002,
    };
    using MONITOR_DEFAULT = MD;

    MD   operator + (MD a)        { return a; }
    MD   operator + (MD a, MD b)  { return MD(UINT(a) | UINT(b)); }
    MD&  operator +=(MD& a, MD b) { return a = a + b; }
    MD   operator - (MD a, MD b)  { return MD(UINT(a) & ~UINT(b)); }
    MD&  operator -=(MD& a, MD b) { return a = a - b; }
    bool operator & (MD a, MD b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class PM : UINT {
        NOREMOVE = 0x0000,
        REMOVE   = 0x0001,
        NOYIELD  = 0x0002,
    };

    PM   operator + (PM a)        { return a; }
    PM   operator + (PM a, PM b)  { return PM(UINT(a) | UINT(b)); }
    PM&  operator +=(PM& a, PM b) { return a = a + b; }
    PM   operator - (PM a, PM b)  { return PM(UINT(a) & ~UINT(b)); }
    PM&  operator -=(PM& a, PM b) { return a = a - b; }
    bool operator & (PM a, PM b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class OBJ : int {
        ANSI_FIXED_FONT     = 11,
        ANSI_VAR_FONT       = 12,
        BLACK_BRUSH         = 4,
        BLACK_PEN           = 7,
        DC_BRUSH            = 18,
        DC_PEN              = 19,
        DEFAULT_GUI_FONT    = 17,
        DEVICE_DEFAULT_FONT = 14,
        DKGRAY_BRUSH        = 3,
        GRAY_BRUSH          = 2,
        LTGRAY_BRUSH        = 1,
        NULL_BRUSH          = 5,
        NULL_PEN            = 8,
        OEM_FIXED_FONT      = 10,
        SYSTEM_FIXED_FONT   = 16,
        SYSTEM_FONT         = 13,
        WHITE_BRUSH         = 0,
        WHITE_PEN           = 6,
    };

    //--------------------------------------------------------------------------

    enum class SW : UINT {
        HIDE            = 0,
        SHOWNORMAL      = 1,
        SHOWMINIMIZED   = 2,
        SHOWMAXIMIZED   = 3,
        MAXIMIZE        = 3,
        SHOWNOACTIVATE  = 4,
        SHOW            = 5,
        MINIMIZE        = 6,
        SHOWMINNOACTIVE = 7,
        SHOWNA          = 8,
        RESTORE         = 9,
        SHOWDEFAULT     = 10,
        FORCEMINIMIZE   = 11,
    };

    //--------------------------------------------------------------------------

    enum class SWP : UINT {
        ASYNCWINDOWPOS = 0x4000,
        DEFERERASE     = 0x2000,
        DRAWFRAME      = 0x0020,
        FRAMECHANGED   = 0x0020,
        HIDEWINDOW     = 0x0080,
        NOACTIVATE     = 0x0010,
        NOCOPYBITS     = 0x0100,
        NOMOVE         = 0x0002,
        NOOWNERZORDER  = 0x0200,
        NOREDRAW       = 0x0008,
        NOREPOSITION   = 0x0200,
        NOSENDCHANGING = 0x0400,
        NOSIZE         = 0x0001,
        NOZORDER       = 0x0004,
        SHOWWINDOW     = 0x0040,
    };

    SWP  operator + (SWP a)         { return a; }
    SWP  operator + (SWP a, SWP b)  { return SWP(UINT(a) | UINT(b)); }
    SWP& operator +=(SWP& a, SWP b) { return a = a + b; }
    SWP  operator - (SWP a, SWP b)  { return SWP(UINT(a) & ~UINT(b)); }
    SWP& operator -=(SWP& a, SWP b) { return a = a - b; }
    bool operator & (SWP a, SWP b)  { return (UINT(a) & UINT(b)) == UINT(b); }

    //--------------------------------------------------------------------------

    enum class WM : UINT {
        NONE                        = 0,
        CREATE                      = 0x0001,
        DESTROY                     = 0x0002,
        MOVE                        = 0x0003,
        SIZE                        = 0x0005,
        ACTIVATE                    = 0x0006,
        SETFOCUS                    = 0x0007,
        KILLFOCUS                   = 0x0008,
        ENABLE                      = 0x000A,
        SETREDRAW                   = 0x000B,
        SETTEXT                     = 0x000C,
        GETTEXT                     = 0x000D,
        GETTEXTLENGTH               = 0x000E,
        PAINT                       = 0x000F,
        CLOSE                       = 0x0010,
        QUERYENDSESSION             = 0x0011,
        QUERYOPEN                   = 0x0013,
        ENDSESSION                  = 0x0016,
        QUIT                        = 0x0012,
        ERASEBKGND                  = 0x0014,
        SYSCOLORCHANGE              = 0x0015,
        SHOWWINDOW                  = 0x0018,
        WININICHANGE                = 0x001A,
        SETTINGCHANGE               = WININICHANGE,
        DEVMODECHANGE               = 0x001B,
        ACTIVATEAPP                 = 0x001C,
        FONTCHANGE                  = 0x001D,
        TIMECHANGE                  = 0x001E,
        CANCELMODE                  = 0x001F,
        SETCURSOR                   = 0x0020,
        MOUSEACTIVATE               = 0x0021,
        CHILDACTIVATE               = 0x0022,
        QUEUESYNC                   = 0x0023,
        GETMINMAXINFO               = 0x0024,
        PAINTICON                   = 0x0026,
        ICONERASEBKGND              = 0x0027,
        NEXTDLGCTL                  = 0x0028,
        SPOOLERSTATUS               = 0x002A,
        DRAWITEM                    = 0x002B,
        MEASUREITEM                 = 0x002C,
        DELETEITEM                  = 0x002D,
        VKEYTOITEM                  = 0x002E,
        CHARTOITEM                  = 0x002F,
        SETFONT                     = 0x0030,
        GETFONT                     = 0x0031,
        SETHOTKEY                   = 0x0032,
        GETHOTKEY                   = 0x0033,
        QUERYDRAGICON               = 0x0037,
        COMPAREITEM                 = 0x0039,
        GETOBJECT                   = 0x003D,
        COMPACTING                  = 0x0041,
        COMMNOTIFY                  = 0x0044,
        WINDOWPOSCHANGING           = 0x0046,
        WINDOWPOSCHANGED            = 0x0047,
        POWER                       = 0x0048,
        COPYDATA                    = 0x004A,
        CANCELJOURNAL               = 0x004B,
        NOTIFY                      = 0x004E,
        INPUTLANGCHANGEREQUEST      = 0x0050,
        INPUTLANGCHANGE             = 0x0051,
        TCARD                       = 0x0052,
        HELP                        = 0x0053,
        USERCHANGED                 = 0x0054,
        NOTIFYFORMAT                = 0x0055,
        CONTEXTMENU                 = 0x007B,
        STYLECHANGING               = 0x007C,
        STYLECHANGED                = 0x007D,
        DISPLAYCHANGE               = 0x007E,
        GETICON                     = 0x007F,
        SETICON                     = 0x0080,
        NCCREATE                    = 0x0081,
        NCDESTROY                   = 0x0082,
        NCCALCSIZE                  = 0x0083,
        NCHITTEST                   = 0x0084,
        NCPAINT                     = 0x0085,
        NCACTIVATE                  = 0x0086,
        GETDLGCODE                  = 0x0087,
        SYNCPAINT                   = 0x0088,
        NCMOUSEMOVE                 = 0x00A0,
        NCLBUTTONDOWN               = 0x00A1,
        NCLBUTTONUP                 = 0x00A2,
        NCLBUTTONDBLCLK             = 0x00A3,
        NCRBUTTONDOWN               = 0x00A4,
        NCRBUTTONUP                 = 0x00A5,
        NCRBUTTONDBLCLK             = 0x00A6,
        NCMBUTTONDOWN               = 0x00A7,
        NCMBUTTONUP                 = 0x00A8,
        NCMBUTTONDBLCLK             = 0x00A9,
        NCXBUTTONDOWN               = 0x00AB,
        NCXBUTTONUP                 = 0x00AC,
        NCXBUTTONDBLCLK             = 0x00AD,
        INPUT_DEVICE_CHANGE         = 0x00FE,
        INPUT                       = 0x00FF,
        KEYDOWN                     = 0x0100,
        KEYFIRST                    = KEYDOWN,
        KEYUP                       = 0x0101,
        CHAR                        = 0x0102,
        DEADCHAR                    = 0x0103,
        SYSKEYDOWN                  = 0x0104,
        SYSKEYUP                    = 0x0105,
        SYSCHAR                     = 0x0106,
        SYSDEADCHAR                 = 0x0107,
        UNICHAR                     = 0x0109,
        KEYLAST                     = UNICHAR,
        IME_STARTCOMPOSITION        = 0x010D,
        IME_ENDCOMPOSITION          = 0x010E,
        IME_COMPOSITION             = 0x010F,
        IME_KEYLAST                 = 0x010F,
        INITDIALOG                  = 0x0110,
        COMMAND                     = 0x0111,
        SYSCOMMAND                  = 0x0112,
        TIMER                       = 0x0113,
        HSCROLL                     = 0x0114,
        VSCROLL                     = 0x0115,
        INITMENU                    = 0x0116,
        INITMENUPOPUP               = 0x0117,
        MENUSELECT                  = 0x011F,
        MENUCHAR                    = 0x0120,
        ENTERIDLE                   = 0x0121,
        MENURBUTTONUP               = 0x0122,
        MENUDRAG                    = 0x0123,
        MENUGETOBJECT               = 0x0124,
        UNINITMENUPOPUP             = 0x0125,
        MENUCOMMAND                 = 0x0126,
        CHANGEUISTATE               = 0x0127,
        UPDATEUISTATE               = 0x0128,
        QUERYUISTATE                = 0x0129,
        CTLCOLORMSGBOX              = 0x0132,
        CTLCOLOREDIT                = 0x0133,
        CTLCOLORLISTBOX             = 0x0134,
        CTLCOLORBTN                 = 0x0135,
        CTLCOLORDLG                 = 0x0136,
        CTLCOLORSCROLLBAR           = 0x0137,
        CTLCOLORSTATIC              = 0x0138,
        MOUSEMOVE                   = 0x0200,
        MOUSEFIRST                  = MOUSEMOVE,
        LBUTTONDOWN                 = 0x0201,
        LBUTTONUP                   = 0x0202,
        LBUTTONDBLCLK               = 0x0203,
        RBUTTONDOWN                 = 0x0204,
        RBUTTONUP                   = 0x0205,
        RBUTTONDBLCLK               = 0x0206,
        MBUTTONDOWN                 = 0x0207,
        MBUTTONUP                   = 0x0208,
        MBUTTONDBLCLK               = 0x0209,
        MOUSEWHEEL                  = 0x020A,
        XBUTTONDOWN                 = 0x020B,
        XBUTTONUP                   = 0x020C,
        XBUTTONDBLCLK               = 0x020D,
        MOUSEHWHEEL                 = 0x020E,
        MOUSELAST                   = MOUSEHWHEEL,
        PARENTNOTIFY                = 0x0210,
        ENTERMENULOOP               = 0x0211,
        EXITMENULOOP                = 0x0212,
        NEXTMENU                    = 0x0213,
        SIZING                      = 0x0214,
        CAPTURECHANGED              = 0x0215,
        MOVING                      = 0x0216,
        POWERBROADCAST              = 0x0218,
        DEVICECHANGE                = 0x0219,
        MDICREATE                   = 0x0220,
        MDIDESTROY                  = 0x0221,
        MDIACTIVATE                 = 0x0222,
        MDIRESTORE                  = 0x0223,
        MDINEXT                     = 0x0224,
        MDIMAXIMIZE                 = 0x0225,
        MDITILE                     = 0x0226,
        MDICASCADE                  = 0x0227,
        MDIICONARRANGE              = 0x0228,
        MDIGETACTIVE                = 0x0229,
        MDISETMENU                  = 0x0230,
        ENTERSIZEMOVE               = 0x0231,
        EXITSIZEMOVE                = 0x0232,
        DROPFILES                   = 0x0233,
        MDIREFRESHMENU              = 0x0234,
        IME_SETCONTEXT              = 0x0281,
        IME_NOTIFY                  = 0x0282,
        IME_CONTROL                 = 0x0283,
        IME_COMPOSITIONFULL         = 0x0284,
        IME_SELECT                  = 0x0285,
        IME_CHAR                    = 0x0286,
        IME_REQUEST                 = 0x0288,
        IME_KEYDOWN                 = 0x0290,
        IME_KEYUP                   = 0x0291,
        MOUSEHOVER                  = 0x02A1,
        MOUSELEAVE                  = 0x02A3,
        NCMOUSEHOVER                = 0x02A0,
        NCMOUSELEAVE                = 0x02A2,
        WTSSESSION_CHANGE           = 0x02B1,
        TABLET_FIRST                = 0x02c0,
        TABLET_LAST                 = 0x02df,
        CUT                         = 0x0300,
        COPY                        = 0x0301,
        PASTE                       = 0x0302,
        CLEAR                       = 0x0303,
        UNDO                        = 0x0304,
        RENDERFORMAT                = 0x0305,
        RENDERALLFORMATS            = 0x0306,
        DESTROYCLIPBOARD            = 0x0307,
        DRAWCLIPBOARD               = 0x0308,
        PAINTCLIPBOARD              = 0x0309,
        VSCROLLCLIPBOARD            = 0x030A,
        SIZECLIPBOARD               = 0x030B,
        ASKCBFORMATNAME             = 0x030C,
        CHANGECBCHAIN               = 0x030D,
        HSCROLLCLIPBOARD            = 0x030E,
        QUERYNEWPALETTE             = 0x030F,
        PALETTEISCHANGING           = 0x0310,
        PALETTECHANGED              = 0x0311,
        HOTKEY                      = 0x0312,
        PRINT                       = 0x0317,
        PRINTCLIENT                 = 0x0318,
        APPCOMMAND                  = 0x0319,
        THEMECHANGED                = 0x031A,
        CLIPBOARDUPDATE             = 0x031D,
        DWMCOMPOSITIONCHANGED       = 0x031E,
        DWMNCRENDERINGCHANGED       = 0x031F,
        DWMCOLORIZATIONCOLORCHANGED = 0x0320,
        DWMWINDOWMAXIMIZEDCHANGE    = 0x0321,
        GETTITLEBARINFOEX           = 0x033F,
        HANDHELDFIRST               = 0x0358,
        HANDHELDLAST                = 0x035F,
        AFXFIRST                    = 0x0360,
        AFXLAST                     = 0x037F,
        PENWINFIRST                 = 0x0380,
        PENWINLAST                  = 0x038F,
        APP                         = 0x8000,
        USER                        = 0x0400,
        CPL_LAUNCH                  = USER + 0x1000,
        CPL_LAUNCHED                = USER + 0x1001,
        SYSTIMER                    = 0x118,
    };

    using WPARAM  = UINT_PTR;
    using LPARAM  = LONG_PTR;
    using WNDPROC = LRESULT(WINAPI*)(HWND,WM,WPARAM,LPARAM);

    //--------------------------------------------------------------------------

    using MONITORENUMPROC = BOOL(WINAPI*)(HMONITOR,HDC,LPRECT,LPVOID);

    //--------------------------------------------------------------------------

    struct WNDCLASSEXA {
        UINT      cbSize        = sizeof(WNDCLASSEXA);
        CS        style         = CS(0);
        WNDPROC   lpfnWndProc   = nullptr;
        int       cbClsExtra    = 0;
        int       cbWndExtra    = 0;
        HINSTANCE hInstance     = nullptr;
        HICON     hIcon         = nullptr;
        HCURSOR   hCursor       = nullptr;
        HBRUSH    hbrBackground = nullptr;
        LPCSTR    lpszMenuName  = nullptr;
        LPCSTR    lpszClassName = nullptr;
        HICON     hIconSm       = nullptr;
    };

    struct MSG {
        HWND   hwnd;
        WM     message;
        WPARAM wParam;
        LPARAM lParam;
        DWORD  time;
        POINT  point;
    };

    struct WINDOWPLACEMENT {
        UINT  cbSize  = sizeof(WINDOWPLACEMENT);
        WPF   flags   = WPF::NONE;
        SW    showCmd = SW::HIDE;
        POINT rcMinPosition;
        POINT rcMaxPosition;
        RECT  rcNormalPosition;
    };

    struct MONITORINFO {
        DWORD        cbSize = sizeof(MONITORINFO);
        RECT         rcMonitor;
        RECT         rcWork;
        MONITORINFOF dwFlags = MONITORINFOF::NONE;
    };

    struct PAINTSTRUCT {
        HDC  hdc;
        BOOL fErase;
        RECT rcPaint;
        BOOL fRestore;
        BOOL fIncUpdate;
        BYTE rgbReserved[32];
    };

    //--------------------------------------------------------------------------

    template<typename To, typename From>
    To to(From);

    template<>
    POINT to(point p) {
        return {LONG(p.x),LONG(p.y)};
    }

    template<>
    point to(POINT p) {
        return {float(p.x),float(p.y)};
    }

    template<>
    RECT to(rect r) {
        return {LONG(r.x),LONG(r.y),LONG(r.x+r.w),LONG(r.y+r.h)};
    }

    template<>
    rect to(RECT r) {
        return {
            float(r.left),
            float(r.top),
            float(r.right-r.left),
            float(r.bottom-r.top),
        };
    }

    template<>
    display to(MONITORINFO m) {
        return {to<rect>(m.rcMonitor),to<rect>(m.rcWork)};
    }

    //--------------------------------------------------------------------------

    extern "C" {

        BOOL WINAPI AdjustWindowRectEx(RECT&,WS,BOOL,WS_EX);

        HDC WINAPI BeginPaint(HWND,PAINTSTRUCT&);

        HWND WINAPI CreateWindowExA(
            WS_EX     dwExStyle,
            LPCSTR    lpClassName,
            LPCSTR    lpWindowName,
            WS        dwStyle,
            int       x,
            int       y,
            int       nWidth,
            int       nHeight,
            HWND      hWndParent,
            HMENU     hMenu,
            HINSTANCE hInstance,
            LPVOID    lpParam
        );

        BOOL WINAPI DestroyWindow(HWND);

        LRESULT WINAPI DefWindowProcA(HWND,WM,WPARAM,LPARAM);

        LRESULT WINAPI DispatchMessageA(const MSG&);

        BOOL WINAPI EndPaint(HWND,const PAINTSTRUCT&);

        BOOL WINAPI EnumDisplayMonitors(HDC,LPCRECT,MONITORENUMPROC,LPVOID);

        int WINAPI FillRect(HDC,const RECT&,HBRUSH);

        HWND WINAPI GetActiveWindow(void);

        BOOL WINAPI GetClientRect (HWND,RECT&);

        HDC WINAPI GetDC(HWND);

        HWND WINAPI GetForegroundWindow(void);

        HMODULE WINAPI GetModuleHandleA(LPCSTR);

        BOOL WINAPI GetMonitorInfoA(HMONITOR,MONITORINFO&);

        DWORD WINAPI GetSysColor(CLR);

        LONG_PTR WINAPI GetWindowLongPtrA(HWND,int);

        BOOL WINAPI GetWindowPlacement(HWND,WINDOWPLACEMENT&);

        BOOL WINAPI GetWindowRect(HWND,RECT&);

        int WINAPI GetWindowTextA(HWND,LPSTR,int);

        int WINAPI GetWindowTextLengthA(HWND);

        BOOL WINAPI IsWindowVisible(HWND);

        BOOL WINAPI IsIconic(HWND);

        BOOL WINAPI IsZoomed(HWND);

        HCURSOR WINAPI LoadCursorA(HINSTANCE,LPCSTR);

        int WINAPI MapWindowPoints(HWND from,HWND to,POINT*,UINT);

        HMONITOR WINAPI MonitorFromPoint(POINT,MONITOR_DEFAULT);

        HMONITOR WINAPI MonitorFromRect(const RECT&,MONITOR_DEFAULT);

        BOOL WINAPI PeekMessageA(MSG&,HWND,WM min,WM max,PM);

        ATOM WINAPI RegisterClassExA(const WNDCLASSEXA&);

        LRESULT WINAPI SendMessageA(HWND,WM,WPARAM,LPARAM);

        HWND WINAPI SetActiveWindow(HWND);

        BOOL WINAPI SetForegroundWindow(HWND);

        LONG_PTR WINAPI SetWindowLongPtrA(HWND,int,LONG_PTR);

        BOOL WINAPI SetWindowPlacement(HWND,const WINDOWPLACEMENT&);

        BOOL WINAPI SetWindowPos(HWND,HWND,int,int,int,int,SWP);

        BOOL WINAPI SetWindowTextA(HWND,LPCSTR);

        BOOL WINAPI ShowWindow(HWND,SW);

        BOOL WINAPI TranslateMessage(const MSG&);

    } // extern "C"

    //--------------------------------------------------------------------------

    library gdi32 {"gdi32.dll"};

    DLLAPI(gdi32,HGDIOBJ,GetStockObject,(OBJ));

    DLLAPI(gdi32,DWORD,SetDCBrushColor,(HDC,DWORD));

    //--------------------------------------------------------------------------

    library shcore {"shcore.dll"};

    DLLAPI(shcore,HRESULT,SetProcessDpiAwareness,(PROCESS_DPI_AWARENESS));

    //--------------------------------------------------------------------------

    template<typename Struct, typename Member>
    constexpr
    uintptr_t offset_of(Member Struct::*member) {
        using struct_ptr = Struct*;
        return uintptr_t(&(struct_ptr(nullptr)->*member));
    }

    //--------------------------------------------------------------------------

    struct AppWindow {
        static const void*  atom;
        static app::window* main;

        LONG_PTR behavior;
        LONG_PTR closed;
        LONG_PTR fullscreen;
        LONG_PTR restore_appearance;
        LONG_PTR restore_showCmd;
        LONG_PTR restore_left;
        LONG_PTR restore_top;
        LONG_PTR restore_right;
        LONG_PTR restore_bottom;

        template<typename T>
        static
        T
        Get(HWND hwnd, LONG_PTR AppWindow::*member) {
            static_assert(sizeof(T) <= sizeof(LONG_PTR),"size mismatch");
            return (T)GetWindowLongPtrA(hwnd,offset_of(member));
        }

        template<typename T>
        static
        void
        Set(HWND hwnd, LONG_PTR AppWindow::*member, T value) {
            static_assert(sizeof(T) <= sizeof(LONG_PTR),"size mismatch");
            SetWindowLongPtrA(hwnd,offset_of(member),LONG_PTR(value));
        }

        static
        app::window::delegate*
        GetBehavior(HWND hwnd) {
            return Get<window::delegate*>(hwnd,&AppWindow::behavior);
        }

        static
        bool
        GetClosed(HWND hwnd) {
            return Get<bool>(hwnd,&AppWindow::closed);
        }

        static
        WS_EX
        GetExStyle(HWND hwnd) {
            return WS_EX(GetWindowLongPtrA(hwnd,int(GWLP::EXSTYLE)));
        }

        static
        bool
        GetFullscreen(HWND hwnd) {
            return Get<bool>(hwnd,&AppWindow::fullscreen);
        }

        static
        app::window::features
        GetRestoreAppearance(HWND hwnd) {
            return Get<window::features>(hwnd,&AppWindow::restore_appearance);
        }

        static
        SW
        GetRestoreShowCmd(HWND hwnd) {
            return Get<SW>(hwnd,&AppWindow::restore_showCmd);
        }

        static
        RECT
        GetRestoreRect(HWND hwnd) {
            return {
                Get<LONG>(hwnd,&AppWindow::restore_left),
                Get<LONG>(hwnd,&AppWindow::restore_top),
                Get<LONG>(hwnd,&AppWindow::restore_right),
                Get<LONG>(hwnd,&AppWindow::restore_bottom),
            };
        }

        static
        WS
        GetStyle(HWND hwnd) {
            return WS(GetWindowLongPtrA(hwnd,int(GWLP::STYLE)));
        }

        static
        void
        SetBehavior(HWND hwnd, window::delegate* behavior) {
            Set(hwnd,&AppWindow::behavior,behavior);
        }

        static
        void
        SetClosed(HWND hwnd, bool closed) {
            Set(hwnd,&AppWindow::closed,closed);
        }

        static
        void
        SetExStyle(HWND hwnd, WS_EX exstyle) {
            SetWindowLongPtrA(hwnd,int(GWLP::EXSTYLE),LONG_PTR(exstyle));
        }

        static
        void
        SetFullscreen(HWND hwnd, bool fullscreen) {
            Set(hwnd,&AppWindow::fullscreen,fullscreen);
        }

        static
        void
        SetRestoreAppearance(HWND hwnd, window::features appearance) {
            Set(hwnd,&AppWindow::restore_appearance,appearance);
        }

        static
        void
        SetRestoreShowCmd(HWND hwnd, SW showCmd) {
            Set(hwnd,&AppWindow::restore_showCmd,showCmd);
        }

        static
        void
        SetRestoreRect(HWND hwnd, RECT exit_fullscreen) {
            Set(hwnd,&AppWindow::restore_left,exit_fullscreen.left);
            Set(hwnd,&AppWindow::restore_top,exit_fullscreen.top);
            Set(hwnd,&AppWindow::restore_right,exit_fullscreen.right);
            Set(hwnd,&AppWindow::restore_bottom,exit_fullscreen.bottom);
        }

        static
        void
        SetStyle(HWND hwnd, WS style) {
            SetWindowLongPtrA(hwnd,int(GWLP::STYLE),LONG_PTR(style));
            SetWindowPos(
                hwnd,HWND_TOP,
                0,0,0,0,
                +SWP::DRAWFRAME
                +SWP::FRAMECHANGED
                +SWP::NOACTIVATE
                +SWP::NOMOVE
                +SWP::NOSIZE
                +SWP::NOZORDER
            );
        }

        static
        LRESULT
        WINAPI
        WindowProc(HWND hwnd, WM msg, WPARAM wp, LPARAM lp) {
            auto const window = (app::window*)hwnd;
            switch (msg) {
                case WM::CLOSE: {
                    bool cancel {false};
                    window->behavior()->closing(window,cancel);
                    if (not cancel) {
                        ShowWindow(hwnd,SW::HIDE);
                        SetClosed(hwnd,true);
                        window->behavior()->closed(window);
                    }
                } return 0;

                // case WM::PAINT: {
                //     PAINTSTRUCT ps;
                //     HDC const hdc {BeginPaint(hwnd,ps)};
                //     SetDCBrushColor(hdc,GetSysColor(CLR::WINDOW));
                //     HBRUSH const hbr {HBRUSH(GetStockObject(OBJ::DC_BRUSH))};
                //     FillRect(hdc,ps.rcPaint,hbr);
                //     EndPaint(hwnd,ps);
                // } return 0;

                default: return DefWindowProcA(hwnd,msg,wp,lp);
            }
        }
    };

    decltype(AppWindow::atom) AppWindow::atom {[]{
        WNDCLASSEXA wcx;
        wcx.style         = CS::OWNDC+CS::HREDRAW+CS::VREDRAW;
        wcx.lpfnWndProc   = AppWindow::WindowProc;
        wcx.cbClsExtra    = 0;
        wcx.cbWndExtra    = sizeof(AppWindow);
        wcx.hInstance     = HINSTANCE(GetModuleHandleA(nullptr));
        wcx.hIcon         = nullptr;
        wcx.hCursor       = LoadCursorA(0,LPCSTR(IDC::ARROW));
        wcx.hbrBackground = HBRUSH(int(CLR::WINDOW)+1);
        wcx.lpszMenuName  = nullptr;
        wcx.lpszClassName = "AppWindow";
        wcx.hIconSm       = nullptr;
        return (void*)uintptr_t(RegisterClassExA(wcx));
    }()};

    decltype(AppWindow::main) AppWindow::main { nullptr };

    static_assert(
        (sizeof(AppWindow) % sizeof(LONG_PTR)) == 0,
        "sizeof(AppWindow) should be an even multiple of sizeof(LONG_PTR)"
    );

}} // namespace app::windows

#undef WINAPI
#undef DLLAPI