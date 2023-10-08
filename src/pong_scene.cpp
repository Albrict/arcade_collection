#include <math.h>
#include "../third_party/imgui.h"
#include "pong_scene.hpp"
#include "graphics.hpp"
#include "collision.hpp"

namespace {
    constexpr float MaxBounceAngle = 75 * DEG2RAD;
    enum MenuButtons : size_t {
        PVP = 0,
        PVE,
        BACK_TO_LOBBY
    };
    enum PauseButtons : size_t {
        CONTINUE = 0,
        BACK_TO_MENU
    };
}

PongScene::PongScene()
    : Scene(),
    racket({Graphics::getResolution().x / 2.f, Graphics::getResolution().y / 2.f, 20.f, 20.f}),
    first_player_score(0),
    second_player_score(0),
    current_state(state::MENU),
    menu_buttons(),
    pause_buttons()
{
    // Initialize UI
    const Vector2 resolution = Graphics::getResolution();
    const std::array<const char*, 5> button_labels = {"PvP", "PvE", "Back to lobby", "Continue", "Back to menu"};
    const float button_width = 215.f;
    const float button_height = 70.f;

    const int initial_x = resolution.x / 2 - button_width / 2;
    int initial_y = resolution.y / 3 - button_height;

    for (int i = 0; i < menu_buttons.size(); ++i) {
        menu_buttons[i] = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[i]);
        initial_y += button_height * 2;
    }
    initial_y = resolution.y / 3 - button_height;
    pause_buttons[CONTINUE] = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[3]);
    initial_y += button_height * 2;
    pause_buttons[BACK_TO_MENU] = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[4]);
    
    // Initialize callbacks
    auto pvp_callback           = [](void *data) { PongScene *scene = static_cast<PongScene*>(data); scene->current_state = state::PLAYER_VS_PLAYER; scene->initializeObjects();};
    auto pve_callback           = [](void *data) { PongScene *scene = static_cast<PongScene*>(data); scene->current_state = state::PLAYER_VS_CPU; scene->initializeObjects(); };
    auto back_to_lobby_callback = [](void *data) { Subject   *subject = static_cast<Subject*>(data); subject->notify(event::BACK_TO_THE_GAME_CHOOSE); };
    auto back_to_menu_callback  = [](void *data) { PongScene *scene = static_cast<PongScene*>(data); scene->current_state = state::MENU; };
    auto continue_callback      = [](void *data) { PongScene *scene = static_cast<PongScene*>(data); scene->current_state = scene->saved_state; };

    menu_buttons[PVP]->setCallback(pvp_callback, this);
    menu_buttons[PVE]->setCallback(pve_callback, this);
    menu_buttons[BACK_TO_LOBBY]->setCallback(back_to_lobby_callback, &this->subject);

    pause_buttons[CONTINUE]->setCallback(continue_callback, this);
    pause_buttons[BACK_TO_MENU]->setCallback(back_to_menu_callback, this);
}

void PongScene::proccessEvents()
{
    switch(current_state) {
    case state::MENU:
        for (auto &button : menu_buttons)
            button->proccessEvents();
        break;
    case state::PAUSE:
        for (auto &button : pause_buttons)
            button->proccessEvents();
        break;
    case state::PLAYER_VS_CPU:
        proccessPlayerVsCPU();
        break;
    case state::PLAYER_VS_PLAYER:
        proccessPlayerVsPlayer();
        break;
    default:
        break;
    }
}

void PongScene::update()
{
    if (current_state == state::PAUSE)
        return;
    if (current_state == state::PLAYER_VS_CPU)
        updatePlayerVsCPU();
    racket.x += velocity.x * GetFrameTime();
    racket.y += velocity.y * GetFrameTime();
    checkBallCollision(first_player);
    checkBallCollision(second_player);
    
}

void PongScene::draw() const 
{
    switch(current_state) {
    case state::MENU:
        drawMenu();
        break;
    case state::PAUSE:
        drawPause();
        [[fallthrough]];
    default:
        const float font_size = 54.f;
        const float middle_x = Graphics::getResolution().x / 2.f;
        DrawLine(middle_x, 0.f, middle_x, Graphics::getResolution().y, WHITE);

        DrawText(TextFormat("%d", first_player_score), middle_x - middle_x / 2.f, Graphics::getResolution().y / 4.f, font_size, WHITE);
        DrawText(TextFormat("%d", second_player_score), middle_x + middle_x / 2.f, Graphics::getResolution().y / 4.f, font_size, WHITE);
        DrawRectangleRec(first_player, WHITE);
        DrawRectangleRec(second_player, WHITE);
        DrawRectangleRec(racket, WHITE);
    }
}

void PongScene::proccessPlayerVsPlayer()
{
    if (IsKeyDown(KEY_ESCAPE)) {
        saved_state = current_state;
        current_state = state::PAUSE;
    }
    if (IsKeyDown(KEY_W)) {
        first_player.y -= 10.f;
        Collision::checkRecBoundsAndLimit(first_player);
    } 
    if (IsKeyDown(KEY_S)) {
        first_player.y += 10.f;
        Collision::checkRecBoundsAndLimit(first_player);
    } 
    if (IsKeyDown(KEY_UP)) {
        second_player.y -= 10.f;
        Collision::checkRecBoundsAndLimit(second_player);
    } 
    if (IsKeyDown(KEY_DOWN)) {
        second_player.y += 10.f;
        Collision::checkRecBoundsAndLimit(second_player);
    }
}

void PongScene::proccessPlayerVsCPU()
{
    if (IsKeyDown(KEY_ESCAPE)) {
        saved_state = current_state;
        current_state = state::PAUSE;
    }
    if (IsKeyDown(KEY_W)) {
        first_player.y -= 10.f;
        Collision::checkRecBoundsAndLimit(first_player);
    } 
    if (IsKeyDown(KEY_S)) {
        first_player.y += 10.f;
        Collision::checkRecBoundsAndLimit(first_player);
    }
}

void PongScene::updatePlayerVsCPU()
{
    if (second_player.y + second_player.height / 2 >= racket.y)
        second_player.y -= 10.f;
    if (second_player.y + second_player.height / 2 <= racket.y)
        second_player.y += 10.f;
 
}
// TODO: Naive ball physics implementation.
// But can be better, check this implementation:
// https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl
void PongScene::checkBallCollision(const Rectangle rect) noexcept
{
    if (racket.x + racket.width >= GetScreenWidth()) {
        ++first_player_score;
        moveBallToTheMiddle();
    }
    if (racket.x <= 0) {
        ++second_player_score;
        moveBallToTheMiddle();
    }
        
    if (racket.y  <= 0) {
        velocity.y = racket_speed;
    }

    if (racket.y + racket.height  >= Graphics::getResolution().y) {
        velocity.y = -racket_speed;
    }

    if (CheckCollisionRecs(racket, rect)) {

        if (velocity.x < 0 || velocity.x > 0) {
            velocity.x *= -1.1;
            velocity.y = (racket.y - rect.y) / (rect.height / 2) * 300.f;

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
    }
}

void PongScene::initializeObjects()
{
    racket = {Graphics::getResolution().x / 2.f, Graphics::getResolution().y / 2.f, 20.f, 20.f};
    first_player_score = 0;
    second_player_score = 0;
    const Vector2 resolution = Graphics::getResolution();
    const float players_width = 10.f;
    const float players_height = 100.f;
    first_player = {.x = 30.f, .y = resolution.y / 2.f, .width = players_width, .height = players_height};
    second_player = {.x = resolution.x - 40.f, .y = resolution.y / 2.f, .width = players_width, .height = players_height};
    
    // Get random direction for racket
    const int direction = GetRandomValue(LEFT, RIGHT);
    if (direction == LEFT)
        velocity = {racket_speed, 0.0f};
    else  
        velocity = {racket_speed * -1.f, 0.0f};
}
