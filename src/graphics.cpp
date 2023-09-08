#include "graphics.hpp"

namespace {
    Vector2 resolution;
};

Vector2 Graphics::getResolution()
{
    return resolution;
}

void Graphics::setResolution(const Vector2 new_resolution) noexcept
{
    resolution = new_resolution;
}
