#pragma once
#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>

namespace app {

    struct display;
    struct point;
    struct rect;
    struct size;

    //--------------------------------------------------------------------------

    void activate();

    bool update(unsigned hertz = 0);

    bool quit();

    //--------------------------------------------------------------------------

    struct point {
        float x = 0, y = 0;

        point() = default;
        point(float x, float y) : x(x), y(y) {}
    };

    point operator +(point p, float d) { return { p.x + d,   p.y + d  }; }
    point operator +(point p, point d) { return { p.x + d.x, p.y + d.y}; }
    point operator -(point p, float d) { return { p.x - d,   p.y - d  }; }
    point operator -(point p, point d) { return { p.x - d.x, p.y - d.y}; }

    //--------------------------------------------------------------------------

    struct size {
        float w = 0, h = 0;

        size() = default;
        size(float s) : w(s), h(s) {}
        size(float w, float h) : w(w), h(h) {}

        bool empty() const { return w == 0 and h == 0; }
    };

    size operator +(size s, size  d) { return { s.w + d.w, s.h + d.h}; }
    size operator -(size s, size  d) { return { s.w - d.w, s.h - d.h}; }
    size operator /(size s, float d) { return { s.w / d,   s.h / d  }; }
    size operator *(size s, float d) { return { s.w * d,   s.h * d  }; }

    //--------------------------------------------------------------------------

    struct rect : point, size {
        rect() = default;
        rect(point p, size s) : point(p), size(s) {}
        rect(float left, float top, float right, float bottom) :
            point(left,top), size(right-left,bottom-top)
        {}

        float left() const { return x; } float right()  const { return x + w; }
        float top()  const { return y; } float bottom() const { return y + h; }
    };

    rect operator +(rect r, float d) { return {{r.x+d,r.y+d},{r.w,r.h}}; }
    rect operator -(rect r, float d) { return {{r.x-d,r.y-d},{r.w,r.h}}; }
    rect operator +(rect r, point d) { return {{r.x+d.x,r.y+d.y},{r.w,r.h}}; }
    rect operator -(rect r, point d) { return {{r.x-d.x,r.y-d.y},{r.w,r.h}}; }
    rect operator +(rect r, size  d) { return {{r.x,r.y},{r.w+d.w,r.h+d.h}}; }
    rect operator -(rect r, size  d) { return {{r.x,r.y},{r.w-d.w,r.h-d.h}}; }
    rect operator /(rect r, float d) { return {{r.x,r.y},{r.w/d,r.h/d}}; }
    rect operator *(rect r, float d) { return {{r.x,r.y},{r.w*d,r.h*d}}; }

    //--------------------------------------------------------------------------

    struct display {
        rect boundary, viewport; float scale = 1; unsigned hertz = 0;

        display() = default;
        display(rect b, rect v) : boundary(b), viewport(v) {}

        static display primary();
    };

    std::vector<display> displays();

    //--------------------------------------------------------------------------

    struct handle {
    protected:
        handle()                           = delete;
        handle(handle&&)                   = delete;
        handle(const handle&)              = delete;
        handle& operator = (handle&&)      = delete;
        handle& operator = (const handle&) = delete;
    };

    //--------------------------------------------------------------------------

    struct interface {
    protected:
        interface()                              = default;
        interface(interface&&)                   = delete;
        interface(const interface&)              = delete;
        interface& operator = (interface&&)      = delete;
        interface& operator = (const interface&) = delete;
        virtual ~interface()                     = default;
    };

    //--------------------------------------------------------------------------

    struct window final : handle {
        struct delegate;
        enum features : unsigned;

        static void operator delete(void*);

        template<typename... Args>
        static window* create(Args...);
        static window* create();

        template<typename... Args>
        static window* main(Args...);
        static window* main();

        template<typename... Args>
        window* configure(Args...);

        void activate(); bool active() const;

        features appearance() const; void appearance(features);

        delegate* behavior() const; void behavior(delegate*);

        std::string title() const; void title(std::string);

        rect boundary() const; void boundary(rect);
        rect viewport() const; void viewport(rect);

        void center();
        void close();      bool closed()     const;
        void fillscreen(); bool fullscreen() const; void fullscreen(bool);
        void hide();       bool hidden()     const; void hidden(bool);
        void maximize();   bool maximized()  const; void maximized(bool);
        void minimize();   bool minimized()  const; void minimized(bool);
        void show();       bool visible()    const; void visible(bool);
        void restore();
    };

    template<typename... Args>
    window*
    window::create(Args... args) {
        auto w = window::create();
        w->configure(args...);
        return w;
    }

    template<typename... Args>
    window*
    window::main(Args... args) {
        auto w = window::main();
        w->configure(args...);
        return w;
    }

    template<typename... Args>
    window*
    window::configure(Args... args) {
        struct local {
        static void set(window& w, window::features   a) { w.appearance(a); }
        static void set(window& w, window::delegate*  b) { w.behavior(b); }
        static void set(window& w, const std::string& t) { w.title(t); }
        static void set(window& w, const char* const  t) { w.title(t); }
        static void set(window& w, const rect&        b) { w.boundary(b); }
        static void unpack(...) {}
        };
        local::unpack((local::set(*this,args),0)...);
        return this;
    }

    //--------------------------------------------------------------------------

    struct window::delegate : interface {
        static delegate* const null;

        virtual void activated(window*) {}
        virtual void attached(window*) {}
        virtual void closing(window*,bool& cancel) {}
        virtual void closed(window*) {}
        virtual void deactivated(window*) {}
        virtual void detached(window*) {}
        virtual void hidden(window*) {}
        virtual void moved(window*) {}
        virtual void resized(window*) {}
        virtual void shown(window*) {}
        virtual void touched(window*) {}
    };

    //--------------------------------------------------------------------------

    enum window::features : unsigned {
        featureless = 0,
        titlebar    = 1 << 0,
        closable    = 1 << 1,
        resizable   = 1 << 2,
        minimizable = 1 << 3,
        maximizable = 1 << 4,
    };

    window::features
    operator +(window::features a) { return a; }

    window::features
    operator +(window::features a, window::features b) {
        return window::features(unsigned(a) | unsigned(b));
    }

    window::features&
    operator +=(window::features& a, window::features b) { return a = a + b; }

    window::features
    operator -(window::features a, window::features b) {
        return window::features(unsigned(a) & ~unsigned(b));
    }

    window::features&
    operator -=(window::features& a, window::features b) { return a = a - b; }

    bool
    operator &(window::features a, window::features b) {
        return (unsigned(a) & unsigned(b)) == unsigned(b);
    }

} // namespace app

std::ostream& operator <<(std::ostream&, const app::point&);
std::ostream& operator <<(std::ostream&, const app::size&);
std::ostream& operator <<(std::ostream&, const app::rect&);
std::ostream& operator <<(std::ostream&, const app::display&);