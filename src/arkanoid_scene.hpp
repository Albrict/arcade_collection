#pragma once
#include <raylib.h>
#include <array>
#include <vector>
#include <memory>
#include "brick.hpp"
#include "graphics.hpp"
#include "scene.hpp"
#include "shapes.hpp"

class ArkanoidScene : public Scene {
    const Rectangle brick_rect;
    Rectangle player;
    Shapes::Circle ball;
    
    std::vector<std::vector<std::unique_ptr<Brick>>> bricks;
public:
    ArkanoidScene();
    ~ArkanoidScene() = default;

    void proccessEvents();
    void update();
    void draw() noexcept;
private:
    void checkCollision();
    std::unique_ptr<Brick> createBrickFrom(const Brick::brickType type, const Rectangle rect);
};
