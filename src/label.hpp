#pragma once
#include <raylib.h>
#include "widget.hpp"

class Label : public Widget {
public:
    Label(const Vector2 position, const char *text, Font font = GetFontDefault(), const int font_size = 28, const int spacing = 2, const Color color = WHITE);
    
    void proccessEvents() {}
    void update() {}
    void draw() const noexcept
    { DrawTextEx(font, text, position, font_size, spacing, color); }

    void changeColor(const Color new_color)
    { color = new_color; }
private:
    int font_size;
    int spacing;
    const char *text;
    
    Vector2 position;
    Color color;
    Font font;
};
