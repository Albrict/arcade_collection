#pragma once
#include "object.hpp"
#include <raylib.h>
#include "collision.hpp"

class PongRacket : public Object {
public:
    enum class Message {
        FIRST_PLAYER_WIN,
        SECOND_PLAYER_WIN
    };

    explicit PongRacket(const unsigned int pong_scene_id, const unsigned int first_player_id, const unsigned int second_player_id, const Rectangle racket, const Color color)
        : pong_scene_id(pong_scene_id), first_player_id(first_player_id), second_player_id(second_player_id), racket_rect(racket), racket_color(color) {};
    ~PongRacket() = default;

    void proccessEvents() override;
    void update() override;
    void draw() const override 
    { DrawRectangleRec(racket_rect, racket_color); }
private:
    bool collision = false;
    const unsigned int first_player_id;
    const unsigned int second_player_id;
    const unsigned int pong_scene_id;
    Rectangle rect;
    const float racket_speed = 550.f;
    Vector2 velocity = {racket_speed, 0.0f};
    Rectangle racket_rect;
    Color racket_color;
};
