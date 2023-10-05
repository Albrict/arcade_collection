#pragma once
#include <raylib.h>

class Brick {
public: 
    enum brickType {
        SOFT,
        MIDDLE,
        HARD,
        DESTROYED
    };
    Brick(const brickType type, const Rectangle brick_rect, const Color brick_color, const unsigned int brick_health)
        : type(type), rect(brick_rect), color(brick_color), health(brick_health) {}
    virtual ~Brick() = default;
    
    virtual void update() = 0; 
    virtual void draw() const noexcept = 0;

    Rectangle getBrickRect() const  noexcept
    { return rect; }
    void damageBrick() noexcept
    { if (health - 10 < 0) return; else health -= 10; }
    int getHealth() const noexcept
    { return health; }
    brickType getBrickType() const noexcept
    { return type; }
protected:
    const Rectangle rect;
    Color color;
    brickType type;
private:
    int health;
};
