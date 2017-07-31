#pragma once

namespace app {
namespace macos {

    struct NSDate : NSObject {

        static struct API {

            objc::classid cls {"NSDate"};

            objc::message<NSDate*()>
            date {"date"};

            objc::message<NSDate*(double)>
            dateWithTimeIntervalSinceNow {"dateWithTimeIntervalSinceNow:"};

            objc::message<NSDate*()>
            distantPast {"distantPast"};

            objc::message<double(NSDate*)>
            timeIntervalSinceDate {"timeIntervalSinceDate:"};

        } api;

        static
        NSDate*
        date() { return api.date(api.cls); }

        static
        NSDate*
        dateWithTimeIntervalSinceNow(double interval) {
            return api.dateWithTimeIntervalSinceNow(api.cls,interval);
        }

        static
        NSDate*
        distantPast() { return api.distantPast(api.cls); }

        double
        timeIntervalSinceDate(NSDate* date) {
            return api.timeIntervalSinceDate(this,date);
        }

    };

    NSDate::API NSDate::api {};

}} // namespace app::macos