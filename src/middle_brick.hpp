#pragma once
#include "brick.hpp"

class MiddleBrick : public Brick {
public:
    MiddleBrick(const Rectangle rect)
        : Brick(brickType::MIDDLE, rect, YELLOW, 20) {};
    ~MiddleBrick() = default;
    
    void draw() const noexcept
    {
        DrawRectangleRec(rect, color);
    }

    void update()
    {
       if (Brick::getHealth() == 10)
            color = GRAY; 
    }
};
