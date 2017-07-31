#pragma once

namespace app {
namespace macos {

    struct NSMenu;

    struct NSMenuItem : NSObject {

        static struct API {

            objc::classid cls {"NSMenuItem"};

            objc::message<NSMenuItem*(NSString*,objc::selector,NSString*)>
            initWithTitle_action_keyEquivalent
            {"initWithTitle:action:keyEquivalent:"};

            objc::message<void(NSMenu*)>
            setSubmenu {"setSubmenu:"};

            objc::message<void(NSObject*)>
            setTarget {"setTarget:"};

            objc::message<NSMenu*()>
            submenu {"submenu"};

            objc::message<NSObject*()>
            target {"target"};

        } api;

        static
        NSMenuItem*
        alloc() { return NSObject::alloc<NSMenuItem>(); }

        static
        NSMenuItem*
        menuItem() { return alloc()->init(); }

        static
        NSMenuItem*
        menuItem(
            NSString*      title,
            objc::selector action,
            NSString*      keyEquivalent
        ) { return alloc()->init(title,action,keyEquivalent); }

        NSMenuItem*
        init() { return NSObject::init<NSMenuItem>(); }

        NSMenuItem*
        init(
            NSString*      title,
            objc::selector action,
            NSString*      keyEquivalent
        ) {
            return api.initWithTitle_action_keyEquivalent(
                this,title,action,keyEquivalent
            );
        }

        void
        setSubmenu(NSMenu* submenu) { api.setSubmenu(this,submenu); }

        void
        setTarget(NSObject* target) { api.setTarget(this,target); }

        NSMenu*
        submenu() { return api.submenu(this); }

        NSObject*
        target() { return api.target(this); }

    };

    NSMenuItem::API NSMenuItem::api {};

}} // namespace app::macos