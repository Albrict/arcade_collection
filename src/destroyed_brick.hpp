#pragma once
#include "brick.hpp"

class DestroyedBrick final : public Brick {
public:
    DestroyedBrick(const Rectangle rect)
        : Brick(brickType::DESTROYED, rect, DARKBLUE, 0) {};
    ~DestroyedBrick() = default;
    
    void proccessEvents() override {}
    void update() override {}
    void draw() const override {}
};
