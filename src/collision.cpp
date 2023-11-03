#include "collision.hpp"
#include "graphics.hpp"

void Collision::checkRecBoundsAndLimit(Rectangle &rect)
{
    if (rect.y + rect.height >= Graphics::getResolution().y)
        rect.y = Graphics::getResolution().y - rect.height;
    if (rect.y <= 0.f)
        rect.y = 0.f;
    if (rect.x + rect.width >= Graphics::getResolution().x)
        rect.x = Graphics::getResolution().x - rect.width;
    if (rect.x <= 0.f)
        rect.x = 0.f;
}

void Collision::checkCircleBoundsAndLimit(Shapes::Circle &circle)
{
    if (circle.radius + circle.position.x >= Graphics::getResolution().x)
        circle.position.x = Graphics::getResolution().x - circle.radius;
}
