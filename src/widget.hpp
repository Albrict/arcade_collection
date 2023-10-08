#pragma once
#include <functional>
#include <memory>

class Widget {
public:
    using unique_ptr = std::unique_ptr<Widget>;
    virtual ~Widget() {}

    virtual void proccessEvents() = 0;
    virtual void update() = 0;
    virtual void draw() const noexcept = 0;

    static int getDefaultFontSize()
    { return 28; }
protected:
    using callback = std::function<void(void*)>;     
};
