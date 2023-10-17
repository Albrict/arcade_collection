#pragma once
#include "brick.hpp"

class SoftBrick final : public Brick {
public:
    SoftBrick(const Rectangle rect)
        : Brick(brickType::SOFT, rect, GREEN, 10) {};
    ~SoftBrick() = default;
    
    void proccessEvents() override {} 
    void update() override {}
    void draw() const override  
    { DrawRectangleRec(rect, color); }
};
