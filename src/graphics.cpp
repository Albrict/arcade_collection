#include "graphics.hpp"

namespace Graphics {
    Vector2 resolution = {0, 0};
};

Vector2 Graphics::getResolution()
{
    return resolution;
}

void Graphics::setResolution(const Vector2 new_resolution)
{
    resolution = new_resolution; 
}
