#pragma once

namespace app {
namespace macos {

    struct NSMenuItem;

    //--------------------------------------------------------------------------

    struct NSMenu : NSObject {

        static struct API {

            objc::classid cls {"NSMenu"};

            objc::message<void(NSMenuItem*)>
            addItem {"addItem:"};

            objc::message<NSMenu*(NSString*)>
            initWithTitle {"initWithTitle:"};

            objc::message<void()>
            update {"update"};

        } api;

        static
        NSMenu*
        alloc() { return NSObject::alloc<NSMenu>(); }

        NSMenu*
        init() { return NSObject::init<NSMenu>(); }

        NSMenu*
        init(NSString* title) { return api.initWithTitle(this,title); }

        static
        NSMenu*
        menu() { return alloc()->init(); }

        static
        NSMenu*
        menu(NSString* title) { return alloc()->init(title); }

        void
        addItem(NSMenuItem* item) { api.addItem(this,item); }

        void
        update() { api.update(this); }

    };

    NSMenu::API NSMenu::api {};

}} // namespace app::macos