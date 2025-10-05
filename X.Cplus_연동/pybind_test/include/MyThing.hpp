#pragma once
#include <string>

class MyThing {
public:
    explicit MyThing(int value = 0) : value_(value) {}

    // 멤버 메소드
    int increment(int delta) {
        value_ += delta;
        return value_;
    }

    // 정적 메소드
    static const char* version() {
        return "MyThing/1.0";
    }

    // getter / setter
    int get_value() const { return value_; }
    void set_value(int v) { value_ = v; }

private:
    int value_;
};
