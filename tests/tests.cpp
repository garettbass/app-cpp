#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.hpp"

#include <algorithm>
#include <string>
#include "../app.hpp"

using namespace doctest;

TEST_CASE("objc::classid") {
    objc::classid NSObject { "NSObject" };
    REQUIRE(NSObject.cls != nullptr);
    REQUIRE(NSObject.name() == std::string("NSObject"));
}

TEST_CASE("objc::protocol") {
    objc::protocol NSTextViewDelegate { "NSTextViewDelegate" };
    REQUIRE(NSTextViewDelegate.proto != nullptr);
    REQUIRE(NSTextViewDelegate.name() == std::string("NSTextViewDelegate"));
}

TEST_CASE("objc::selector") {
    objc::selector alloc { "alloc" };
    REQUIRE(alloc.sel != nullptr);
    REQUIRE(alloc.name() == std::string("alloc"));
}

TEST_CASE("objc::super") {
    objc::classid NSObject { "NSObject" };
    objc::classid TestClass1 { "TestClass1",NSObject };
    REQUIRE(TestClass1.cls != nullptr);
    REQUIRE(TestClass1.name() == std::string("TestClass1"));
    auto obj = objc::alloc(TestClass1);
    auto super = objc::super(obj);
    REQUIRE(objc::classof(super) == NSObject);
}

TEST_CASE("objc::retain/release") {
    static bool initialized = false;
    static bool deallocated = false;

    objc::classid TestClass2 {
        "TestClass2","NSObject",
        objc::method("init",[](id self,SEL sel){
            self = objc::message<id()>{sel}(objc::super(self));
            initialized = true;
        }),
        objc::method("dealloc",[](id self,SEL sel){
            deallocated = true;
            objc::message<void()>{sel}(objc::super(self));
        })
    };

    REQUIRE(not initialized);
    REQUIRE(not deallocated);

    objc::object obj = alloc(TestClass2);
    REQUIRE(initialized);
    REQUIRE(not deallocated);
    REQUIRE(get_retain_count(obj) == 1);

    objc::retain(obj);
    REQUIRE(get_retain_count(obj) == 2);

    objc::release(obj);
    REQUIRE(get_retain_count(obj) == 1);

    objc::release(obj);
    REQUIRE(deallocated);
}

int main(int argc, char * argv[]) {
    objc::autoreleasepool autoreleasepool;
    Context context { argc, argv };
    const int failures = context.run();
    return std::min(failures,255);
}
