#pragma once
#include "brick.hpp"

class HardBrick : public Brick {
public:
    HardBrick(const Rectangle rect)
        : Brick(brickType::HARD, rect, RED, 100) {};
    ~HardBrick() = default;
    
    void draw() const noexcept
    {
        DrawRectangleRec(rect, color);
    }
    void update()
    {
       ; 
    }
};
