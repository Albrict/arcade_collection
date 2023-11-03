#pragma once
#include "brick.hpp"

class HardBrick final : public Brick {
public:
    HardBrick(const Rectangle rect)
        : Brick(brickType::HARD, rect, RED, 30) {};
    ~HardBrick() = default;
    
    void proccessEvents() override {}
    void draw() const override  
    { DrawRectangleRec(rect, color); }
    void update() override
    {   
        if (Brick::getHealth() == 20)
            color = YELLOW; 
        if (Brick::getHealth() == 10)
            color = GREEN;
    }
};
