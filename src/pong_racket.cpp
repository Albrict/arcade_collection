#include "pong_racket.hpp"
#include "graphics.hpp"
#include "message_system.hpp"

void PongRacket::proccessEvents()
{
    std::any rect_data = MessageSystem::getMessage(Object::object_id);
    if (rect_data.has_value()) {
        rect = *std::any_cast<Rectangle*>(rect_data);
        collision = true;
    }
    MessageSystem::sendMessage(first_player_id, &racket_rect, Object::object_id);
    MessageSystem::sendMessage(second_player_id, &racket_rect, Object::object_id);
}

void PongRacket::update()
{
    if (collision) {
        if (velocity.x < 0 || velocity.x > 0) {
            velocity.x *= -1.1;
            velocity.y = (racket_rect.y - rect.y) / (rect.height / 2) * 300.f;
            // Limit speed
            if (velocity.x >= 1000.f)
                velocity.x = 1000.f;
            if (velocity.x <= -1000.f)
                velocity.x = -1000.f;

            if (velocity.y >= 1000.f)
                velocity.y = 1000.f;
            if (velocity.y == -1000.f)
                velocity.y = -1000.f;
        }
        collision = false;
    }
    if (racket_rect.y  <= 0)
        velocity.y = racket_speed;
    if (racket_rect.y + racket_rect.height  >= Graphics::getResolution().y)
        velocity.y = -racket_speed;

    if (racket_rect.x + racket_rect.width >= GetScreenWidth()) {
        std::any msg = Message::FIRST_PLAYER_WIN;
        MessageSystem::sendMessage(pong_scene_id, msg, Object::object_id); 
        racket_rect.x = Graphics::getResolution().x / 2.f;
        racket_rect.y = Graphics::getResolution().y / 2.f;
        velocity.x = racket_speed;
        velocity.y = 0.0f;
    } else if (racket_rect.x  <= 0) {
        std::any msg = Message::SECOND_PLAYER_WIN;
        MessageSystem::sendMessage(pong_scene_id, msg);
        racket_rect.x = Graphics::getResolution().x / 2.f;
        racket_rect.y = Graphics::getResolution().y / 2.f;
        velocity.x = racket_speed;
        velocity.y = 0.0f;
    }

    racket_rect.x += velocity.x * GetFrameTime();
    racket_rect.y += velocity.y * GetFrameTime();
}
