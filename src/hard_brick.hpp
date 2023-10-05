#pragma once
#include "brick.hpp"

class HardBrick : public Brick {
public:
    HardBrick(const Rectangle rect)
        : Brick(brickType::HARD, rect, RED, 30) {};
    ~HardBrick() = default;
    
    void draw() const noexcept
    {
        DrawRectangleRec(rect, color);
    }
    void update()
    {
        if (Brick::getHealth() == 20)
            color = DARKPURPLE; 
        if (Brick::getHealth() == 10)
            color = DARKBLUE;
    }
};
