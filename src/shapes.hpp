#pragma once
#include <raylib.h>

namespace Shapes {
    struct Circle {
        Vector2 position;
        Vector2 velocity;
        const float radius;

        Circle(const Vector2 position, const Vector2 velocity, const float radius)
            : position(position), velocity(velocity), radius(radius) {}
    };
};
