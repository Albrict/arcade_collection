#pragma once
#include <raylib.h>
namespace Graphics {
    Vector2 getResolution();
    void setResolution(const Vector2 new_resolution) noexcept;
        
    inline constexpr Vector2 getGeneralButtonSize()
    { return {200.f, 70.f}; }
}
