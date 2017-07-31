#pragma once

#pragma once

namespace app {
namespace ios {

    struct UIColor : NSObject {

        static struct API {

            objc::classid cls {"UIColor"};

            objc::message<UIColor*()>
            blackColor {"blackColor"};

            objc::message<UIColor*()>
            blueColor {"blueColor"};

            objc::message<UIColor*()>
            brownColor {"brownColor"};

            objc::message<UIColor*()>
            clearColor {"clearColor"};

            objc::message<UIColor*(CGFloat,CGFloat,CGFloat,CGFloat)>
            colorWithRed_green_blue_alpha {"colorWithRed:green:blue:alpha:"};

            objc::message<UIColor*()>
            cyanColor {"cyanColor"};

            objc::message<UIColor*()>
            darkGrayColor {"darkGrayColor"};

            objc::message<UIColor*()>
            grayColor {"grayColor"};

            objc::message<UIColor*()>
            greenColor {"greenColor"};

            objc::message<UIColor*()>
            lightGrayColor {"lightGrayColor"};

            objc::message<UIColor*()>
            magentaColor {"magentaColor"};

            objc::message<UIColor*()>
            orangeColor {"orangeColor"};

            objc::message<UIColor*()>
            purpleColor {"purpleColor"};

            objc::message<UIColor*()>
            redColor {"redColor"};

            objc::message<UIColor*()>
            whiteColor {"whiteColor"};

            objc::message<UIColor*()>
            yellowColor {"yellowColor"};

        } api;

        static
        UIColor*
        color(CGFloat r, CGFloat g, CGFloat b, CGFloat a) {
            return api.colorWithRed_green_blue_alpha(api.cls,r,g,b,a);
        }

        static
        UIColor*
        blackColor() { return api.blackColor(api.cls); }

        static
        UIColor*
        blueColor() { return api.blueColor(api.cls); }

        static
        UIColor*
        brownColor() { return api.brownColor(api.cls); }

        static
        UIColor*
        clearColor() { return api.clearColor(api.cls); }

        static
        UIColor*
        cyanColor() { return api.cyanColor(api.cls); }

        static
        UIColor*
        darkGrayColor() { return api.darkGrayColor(api.cls); }

        static
        UIColor*
        grayColor() { return api.grayColor(api.cls); }

        static
        UIColor*
        greenColor() { return api.greenColor(api.cls); }

        static
        UIColor*
        lightGrayColor() { return api.lightGrayColor(api.cls); }

        static
        UIColor*
        magentaColor() { return api.magentaColor(api.cls); }

        static
        UIColor*
        orangeColor() { return api.orangeColor(api.cls); }

        static
        UIColor*
        purpleColor() { return api.purpleColor(api.cls); }

        static
        UIColor*
        redColor() { return api.redColor(api.cls); }

        static
        UIColor*
        whiteColor() { return api.whiteColor(api.cls); }

        static
        UIColor*
        yellowColor() { return api.yellowColor(api.cls); }

    };

    UIColor::API UIColor::api {};

}} // namespace app::ios
