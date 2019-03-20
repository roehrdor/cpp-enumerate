#include "catch/catch.hpp"
#include <enumerate.hpp>
#include <vector>

struct Bob {
    int x;
    friend int* begin( Bob& b ){ return &b.x; }
    friend int* end( Bob& b ){ return &b.x+1; }
};

struct Foo {
    int x;
    int * begin() { return &x; }
    int * end() { return &x + 1; }
};

namespace adltest
{
struct Foo {};
int * begin(Foo& f) { return reinterpret_cast<int*>(&f); }
int * end(Foo& f) { return reinterpret_cast<int*>(&f); }
}

TEST_CASE ("Custom iterable type (friend)", "enumerate") {
    {
        int x = 0, y = 0, cnt = 0;
        Foo f{3};
        for (auto&& e : f) { x += e; }
        for (auto&& [idx, val]: rz::enumerate(f)) {
            y += val;
            REQUIRE ( cnt++ == idx );
        }
        REQUIRE ( x == y );
    }
    {
        int x = 0, y = 0, cnt = 0;
        for (auto&& e : Foo{7}) { x += e; }
        for (auto&& [idx, val] : rz::enumerate(Foo{7})) {
            y += val;
            REQUIRE ( cnt++ == idx );
        }
        REQUIRE ( x == y );
    }
}

TEST_CASE ("Custom iterable type", "enumerate") {
    {
        int x = 0, y = 0, cnt = 0;
        Bob b{3};
        for (auto&& e : b) { x += e; }
        for (auto&& [idx, val]: rz::enumerate(b)) {
            y += val;
            REQUIRE ( cnt++ == idx );
        }
        REQUIRE ( x == y );
    }
    {
        int x = 0, y = 0, cnt = 0;
        for (auto&& e : Bob{7}) { x += e; }
        for (auto&& [idx, val] : rz::enumerate(Bob{7})) {
            y += val;
            REQUIRE ( cnt++ == idx );
        }
        REQUIRE ( x == y );
    }
}

TEST_CASE ("Custom iterable type (ADL)", "enumerate") {
    {
        int x = 0, y = 0, cnt = 0;
        adltest::Foo f{};
        for (auto&& e : f) { x += e; }
        for (auto&& [idx, val]: rz::enumerate(f)) {
            y += val;
            REQUIRE ( cnt++ == idx );
        }
        REQUIRE ( x == y );
    }
    {
        int x = 0, y = 0, cnt = 0;
        for (auto&& e : adltest::Foo{}) { x += e; }
        for (auto&& [idx, val] : rz::enumerate(adltest::Foo{})) {
            y += val;
            REQUIRE ( cnt++ == idx );
        }
        REQUIRE ( x == y );
    }
}

TEST_CASE ("iterate over container", "enumerate") {
    {
        int sum = 0, cnt = 0;
        std::vector<int> v{1, 2, 3, 4};
        for (auto&& [idx, val] : rz::enumerate(v)) {
            ++val;
            sum += val;
            REQUIRE ( cnt++ == idx ) ;
        }
        REQUIRE ( sum == 14 );
        REQUIRE ( v[0] == 2 );
        REQUIRE ( v[1] == 3 );
        REQUIRE ( v[2] == 4 );
        REQUIRE ( v[3] == 5 );
    }
    {
        int sum = 0, cnt = 0;
        for (auto&& [idx, val] : rz::enumerate(std::vector<int>{1, 2, 3, 4})) {
            ++val;
            sum += val;
            REQUIRE ( cnt++ == idx ) ;
        }
        REQUIRE ( sum == 14 );
    }
}
