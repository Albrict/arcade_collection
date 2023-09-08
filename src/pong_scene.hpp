#pragma once
#include <raylib.h>
#include "scene.hpp"
#include "graphics.hpp"

class PongScene : public Scene {
    Rectangle first_player;
    Rectangle second_player;
    Rectangle racket;
    Vector2 velocity;
    enum direction {
        LEFT = 0,
        RIGHT
    };

    unsigned int first_player_score;
    unsigned int second_player_score;
    float racket_speed = 550.f;
public:
    PongScene();
    ~PongScene() = default;

    void proccessEvents();
    void update();
    void draw() noexcept;
private:
    void checkBallCollision(const Rectangle rect) noexcept;
    void moveBallToTheMiddle() noexcept
    {
        const int direction = GetRandomValue(LEFT, RIGHT);
        racket.x = Graphics::getResolution().x / 2.f;
        racket.y = Graphics::getResolution().y / 2.f;

        if (direction == LEFT)
            velocity = {racket_speed, 0.0f};
        else  
            velocity = {racket_speed * -1.f, 0.0f};
    }
};
