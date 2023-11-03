#pragma once
#include <filesystem>
#include "brick.hpp"
#include "simple_button.hpp"
#include "graphics.hpp"
#include "scene.hpp"
#include "shapes.hpp"

class ArkanoidScene : public Scene {
public:
    ArkanoidScene();
    ~ArkanoidScene() = default;

    void proccessEvents() override;
    void update() override;
    void draw() const override;
private:
    void drawBrick(const Brick::brickType, const Rectangle rect) const;
    void loadLevel(const std::filesystem::path &path);
    void proccessLevelMenu();
    void proccessGame();
    void checkBallCollisionAndBounce();
    void checkPlayerCollisionWithBall(); 
    void checkCollisionWithBrick(Brick *brick);
    std::unique_ptr<Brick> createBrickFrom(const Brick::brickType type, const Rectangle rect);
private:
    enum class state {
        LEVEL_MENU,
        PAUSE,
        GAME
    };
      
    bool ball_active;
    Rectangle player;
    state current_state;

    std::vector<std::vector<std::unique_ptr<Brick>>> bricks;
    std::vector<std::vector<Brick::brickType>> brick_grid;
    std::unique_ptr<Shapes::Circle> ball;
    std::array<SimpleButton::unique_ptr, 4> level_menu_buttons;
    std::array<SimpleButton::unique_ptr, 2> pause_buttons;
};
