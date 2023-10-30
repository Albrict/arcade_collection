#pragma once
#include <raylib.h>
#include "widget.hpp"

class Label : public Widget {
public:
    Label(const Vector2 position, const char *text, Font font = GetFontDefault(), const int font_size = 28, const int spacing = 2, const Color color = WHITE);

    void proccessEvents() override
    { if (callback) callback(data); }
    void update() override {}
    void draw() const override
    { DrawTextEx(font, text, position, font_size, spacing, color); }

    void changeColor(const Color new_color)
    { color = new_color; }
    void updateLabel(const char *newText) noexcept
    { text = newText; }

    void setCallback(Widget::callback p_callback, void *p_data)
    { callback = p_callback; data = p_data; }
private:
    void *data;
    Widget::callback callback;

    int font_size;
    int spacing;
    const char *text;
    
    Vector2 position;
    Color color;
    Font font;
};
