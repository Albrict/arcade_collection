#pragma once
#include "object.hpp"
#include <functional>
#include <memory>

class Widget : public Object {
public:
    using callback = std::function<void(void*)>;     
    using unique_ptr = std::unique_ptr<Widget>;
    Widget()
        : Object() {}
    virtual ~Widget() = default;

    virtual void proccessEvents() override = 0;
    virtual void update() override = 0;
    virtual void draw() const override = 0;

    static int getDefaultFontSize()
    { return 28; }
};
