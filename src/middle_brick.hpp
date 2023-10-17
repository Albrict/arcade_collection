#pragma once
#include "brick.hpp"

class MiddleBrick final : public Brick {
public:
    MiddleBrick(const Rectangle rect)
        : Brick(brickType::MIDDLE, rect, YELLOW, 20) {};
    ~MiddleBrick() = default;
   
    void proccessEvents() override {}
    void draw() const override
    { DrawRectangleRec(rect, color); }

    void update() override
    { if (Brick::getHealth() == 10) color = GREEN; }
};
