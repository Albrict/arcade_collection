#pragma once
#include <raylib.h>
#include <array>
#include <vector>
#include <memory>
#include "graphics.hpp"
#include "scene.hpp"
#include "shapes.hpp"

class ArkanoidScene : public Scene {
    enum class brickType {
        SOFT,
        MIDDLE,
        HARD,
        DESTROYED
    };
    struct Brick {
        brickType type;
        Color color;
        Rectangle brick_rect;
        Brick(const brickType type, const Rectangle brick_rect);
    };
    std::array<std::vector<std::unique_ptr<Brick>>, 4> bricks;
    const Rectangle brick_rect;
    Rectangle player;
    Shapes::Circle ball;
public:
    ArkanoidScene();
    ~ArkanoidScene() = default;

    void proccessEvents();
    void update();
    void draw() noexcept;
private:
    void checkCollision();
};
