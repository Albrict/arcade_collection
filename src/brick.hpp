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
        : rect(brick_rect), color(brick_color), health(brick_health) {}
    virtual ~Brick() = default;
    
    virtual void update() = 0; 
    virtual void draw() const noexcept = 0;

    Rectangle getBrickRect() const 
    { return rect; }
protected:
    void damageBrick(const unsigned int damage)
    { if (health - damage < 0) return; else health -= damage; }
    int getHealth() const noexcept
    { return health; }
protected:
    const Rectangle rect;
    Color color;
private:
    int health;
};
