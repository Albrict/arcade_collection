#pragma once
#include "brick.hpp"

class SoftBrick final : public Brick {
public:
    SoftBrick(const Rectangle rect)
        : Brick(brickType::SOFT, rect, GREEN, 10) {};
    ~SoftBrick() = default;
    
    void draw() const noexcept
    {
        DrawRectangleRec(rect, color);
    }
    void update()
    {
       ; 
    }
};
