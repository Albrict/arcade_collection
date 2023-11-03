#pragma once
#include <raylib.h>
#include "shapes.hpp"

namespace Collision {
    void checkRecBoundsAndLimit(Rectangle &rect);
    void checkCircleBoundsAndLimit(Shapes::Circle &circle);
}
