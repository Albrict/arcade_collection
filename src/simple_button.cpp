#include "simple_button.hpp"

SimpleButton::SimpleButton(const float x, const float y, const float width, const float height, const char *text, const Color color)
    : data(nullptr),
    callback(nullptr),
    label(nullptr),
    rect({x, y, width, height}),
    button_color(color),
    button_pressed_color(ColorBrightness(color, -0.3f)),
    button_current_color(button_color),
    label_color(BLUE),
    label_pressed_color(ColorBrightness(label_color, -0.3f))
{
    if (text) {
        const int default_font_size = Widget::getDefaultFontSize();
        const int text_width = MeasureText(text, default_font_size); 
        const float label_x = rect.x + (rect.width / 2 - static_cast<int>(text_width / 2));
        const float label_y = rect.y + (rect.height / 2 - static_cast<int>(default_font_size / 2));
        const Vector2 position = {label_x, label_y };
        label = std::make_unique<Label>(position, text, GetFontDefault(), default_font_size, 2, label_color);
    }
}

void SimpleButton::proccessEvents()
{
    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            button_current_color = button_pressed_color;
            label->changeColor(label_pressed_color);
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            button_current_color = button_color;
            label->changeColor(label_color);
            if (callback)
                callback(data);
        }
    } else {
        button_current_color = button_color;
        label->changeColor(label_color);
    }
}
