#pragma once

namespace app {
namespace ios {

    struct UIEvent : NSObject {

        static struct API {

            objc::classid cls {"UIEvent"};

        } api;

    };

    UIEvent::API UIEvent::api {};

}} // namespace app::ios