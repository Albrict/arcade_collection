#pragma once
#include "scene.hpp"
#include "simple_button.hpp"
#include "graphics.hpp"

class PongScene : public Scene {
public:
    PongScene();
    ~PongScene() = default;

    void proccessEvents() override;
    void update() override;
    void draw() const override;
private:
    void proccessPlayerVsPlayer();
    void proccessPlayerVsCPU();
     
    void updatePlayerVsCPU();
    void drawMenu() const
    { for (const auto &button : menu_buttons) button->draw(); }
    void drawPause() const 
    { for (const auto &button : pause_buttons) button->draw(); }

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
private:
    Rectangle first_player;
    Rectangle second_player;
    Rectangle racket;
    Vector2 velocity;

    unsigned int first_player_score;
    unsigned int second_player_score;
    float racket_speed = 550.f;
    
    enum direction {
        LEFT = 0,
        RIGHT
    };

    enum class state {
        MENU,
        PAUSE,
        PLAYER_VS_PLAYER,
        PLAYER_VS_CPU 
    };

    state current_state;
    state saved_state; // Needed for pause state
    std::array<SimpleButton::unique_ptr, 3> menu_buttons;
    std::array<SimpleButton::unique_ptr, 2> pause_buttons;
};
