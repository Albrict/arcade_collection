#pragma once
#include <raylib.h>
#include "../third_party/imgui.h"
namespace Graphics {
    Vector2 getResolution();
    void setResolution(const Vector2 new_resolution) noexcept;
        
    inline constexpr ImVec2 getGeneralButtonSize()
    { return {200.f, 70.f}; }
}
