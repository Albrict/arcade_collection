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
    enum class state {
        LEVEL_MENU,
        GAME
    };
      
    bool ball_active;
    Rectangle player;
    state current_state; 
    std::vector<std::vector<std::unique_ptr<Brick>>> bricks;
    std::unique_ptr<Shapes::Circle> ball;

public:
    ArkanoidScene();
    ~ArkanoidScene() = default;

    void proccessEvents();
    void update();
    void draw() noexcept;
private:
    void proccessLevelMenu();
    void proccessGame();
    void checkBallCollisionAndBounce();
    void checkPlayerCollisionWithBall(); 
    void checkCollisionWithBrick(Brick *brick);
    std::unique_ptr<Brick> createBrickFrom(const Brick::brickType type, const Rectangle rect);
};
