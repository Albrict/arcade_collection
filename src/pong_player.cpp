#include "pong_player.hpp"
#include "collision.hpp"
#include "message_system.hpp"

PongPlayer::PongPlayer(const Rectangle rect, const Color color, const PlayerType type)
    : Object(), player_type(type)
{
    player_rect = rect;
    player_color = color;
}

void PongPlayer::proccessEvents()
{
    unsigned int sender = 0;
    std::any racket_data = MessageSystem::getMessage(Object::object_id, &sender);
    if (racket_data.has_value()) {
        racket_rect = *std::any_cast<Rectangle*>(racket_data);
        if (CheckCollisionRecs(player_rect, racket_rect))
            MessageSystem::sendMessage(sender, &player_rect);
    }

    switch(player_type) {
    case PlayerType::FIRST:
        proccessInputForFirstPlayer();
        break;
    case PlayerType::SECOND:
        proccessInputForSecondPlayer();
        break;
    case PlayerType::CPU:
        ;
        break;
    }

}

void PongPlayer::update()
{
    if (player_type == PlayerType::CPU) {
        if (player_rect.y + player_rect.height / 2 >= racket_rect.y)
            player_rect.y -= 10.f;
        if (player_rect.y + player_rect.height / 2 <= racket_rect.y)
            player_rect.y += 10.f;
    }
}

void PongPlayer::draw() const 
{
    DrawRectangleRec(player_rect, player_color);
}
