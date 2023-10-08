#pragma once
#include "widget.hpp"
#include "label.hpp"

#include <raylib.h>

class SimpleButton : public Widget {
public:
    using unique_ptr = std::unique_ptr<SimpleButton>;
    SimpleButton(const float x, const float y, const float width, const float height, const char *text = nullptr, const Color color = WHITE);
    ~SimpleButton() = default;

    void proccessEvents() override;
    void update() override {}
    void draw() const noexcept override 
    { DrawRectangleRec(rect, button_current_color); if (label) label->draw();}

    void setCallback(Widget::callback p_callback, void *p_data)
    { callback = p_callback; data = p_data; }
private:
    void *data;

    Widget::callback callback;
    std::unique_ptr<Label> label;

    Rectangle rect; 
    Color button_color;
    Color button_pressed_color;
    Color button_current_color;

    Color label_color;
    Color label_pressed_color;
};
