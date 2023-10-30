#include "label.hpp"


Label::Label(const Vector2 p_position, const char *p_text, Font p_font, 
             const int p_font_size, const int p_spacing, const Color p_color)
    : data(nullptr),
    callback(nullptr), 
    position(p_position),
    text(p_text),
    font_size(p_font_size),
    spacing(p_spacing),
    color(p_color),
    font(p_font)
{
     
}
