#pragma once
#include "brick.hpp"

class DestroyedBrick : public Brick {
public:
    DestroyedBrick(const Rectangle rect)
        : Brick(brickType::DESTROYED, rect, DARKBLUE, 0) {};
    ~DestroyedBrick() = default;
    
    void draw() const noexcept
    {
        // Draw nothing since brick is destroyed
        ;
    }
    void update()
    {
       ; 
    }
};
