#pragma once
#include "collision.hpp"
#include "object.hpp"
#include <raylib.h>

class PongPlayer : public Object {
public:
    enum class PlayerType {
        FIRST,
        SECOND,
        CPU
    };
    explicit PongPlayer(const Rectangle rect, const Color color, const PlayerType type);
    ~PongPlayer() = default;

    void proccessEvents() override;
    void update() override;
    void draw() const override;
private:
    void proccessInputForFirstPlayer()
    {
        if (IsKeyDown(KEY_W)) {
            player_rect.y -= 10.f;
            Collision::checkRecBoundsAndLimit(player_rect);
        } 
        if (IsKeyDown(KEY_S)) {
            player_rect.y += 10.f;
            Collision::checkRecBoundsAndLimit(player_rect);
        } 
    }
    void proccessInputForSecondPlayer()
    {
        if (IsKeyDown(KEY_UP)) {
            player_rect.y -= 10.f;
            Collision::checkRecBoundsAndLimit(player_rect);
        } 
        if (IsKeyDown(KEY_DOWN)) {
            player_rect.y += 10.f;
            Collision::checkRecBoundsAndLimit(player_rect);
        } 
    }
private:
    const PlayerType player_type;
    Rectangle player_rect;
    Rectangle racket_rect;
    Color player_color;
};
