#include <math.h>
#include "../third_party/imgui.h"
#include "pong_scene.hpp"
#include "graphics.hpp"

namespace {
    constexpr float MaxBounceAngle = 75 * DEG2RAD;
    void checkRecBounds(Rectangle &rect)
    {
        if (rect.y + rect.height >= Graphics::getResolution().y)
            rect.y = Graphics::getResolution().y - rect.height;
        else if (rect.y <= 0.f)
            rect.y = 0.f;
    }
}

PongScene::PongScene()
    : racket({Graphics::getResolution().x / 2.f, Graphics::getResolution().y / 2.f, 20.f, 20.f}),
    first_player_score(0),
    second_player_score(0),
    current_state(state::MENU)
{
    const Vector2 resolution = Graphics::getResolution();
    const float players_width = 10.f;
    const float players_height = 100.f;
    first_player = {.x = 30.f, .y = resolution.y / 2.f, .width = players_width, .height = players_height};
    second_player = {.x = resolution.x - 40.f, .y = resolution.y / 2.f, .width = players_width, .height = players_height};

    const int direction = GetRandomValue(LEFT, RIGHT);
    if (direction == LEFT)
        velocity = {racket_speed, 0.0f};
    else  
        velocity = {racket_speed * -1.f, 0.0f};
}

void PongScene::proccessEvents()
{
    switch(current_state) {
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
    if (current_state == state::PAUSE) {
        return;
    } 
    if (current_state == state::PLAYER_VS_CPU)
        updatePlayerVsCPU();
    racket.x += velocity.x * GetFrameTime();
    racket.y += velocity.y * GetFrameTime();
    checkBallCollision(first_player);
    checkBallCollision(second_player);
}

void PongScene::draw() noexcept
{
    switch(current_state) {
    case state::MENU:
        drawMenu();
        break;
    case state::PAUSE:
        drawPause();
    default:
        const float font_size = 54.f;
        const float middle_x = Graphics::getResolution().x / 2.f;
        DrawLine(middle_x, 0.f, middle_x, Graphics::getResolution().y, WHITE);

        DrawText(TextFormat("Ball velocity x:%f", velocity.x), 0, 0, font_size, WHITE);
        DrawText(TextFormat("Ball velocity y:%f", velocity.y), 0, font_size + 10.f, font_size, WHITE);
    
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
        current_state = state::PAUSE;
    }
    if (IsKeyDown(KEY_W)) {
        first_player.y -= 10.f;
        checkRecBounds(first_player);
    } 
    if (IsKeyDown(KEY_S)) {
        first_player.y += 10.f;
        checkRecBounds(first_player);
    } 
    if (IsKeyDown(KEY_UP)) {
        second_player.y -= 10.f;
        checkRecBounds(second_player);
    } 
    if (IsKeyDown(KEY_DOWN)) {
        second_player.y += 10.f;
        checkRecBounds(second_player);
    }
}

void PongScene::proccessPlayerVsCPU()
{
    if (IsKeyDown(KEY_ESCAPE)) {
        current_state = state::PAUSE;
    }
    if (IsKeyDown(KEY_W)) {
        first_player.y -= 10.f;
        checkRecBounds(first_player);
    } 
    if (IsKeyDown(KEY_S)) {
        first_player.y += 10.f;
        checkRecBounds(first_player);
    }
}

void PongScene::updatePlayerVsCPU()
{
    if (second_player.y + second_player.height / 2 >= racket.y)
        second_player.y -= 10.f;
    if (second_player.y + second_player.height / 2 <= racket.y)
        second_player.y += 10.f;
 
}

void PongScene::drawMenu()
{
    bool opened = true;
    const Vector2 game_resolution = Graphics::getResolution();
    if (ImGui::Begin("Menu", &opened, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | 
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
        ImGui::SetWindowPos({game_resolution.x / 2.f - ImGui::GetWindowWidth() / 2.f, 
                             game_resolution.y / 2.f - ImGui::GetWindowHeight() / 2.f});
        ImGui::SetWindowFontScale(2.f);
        if (ImGui::Button("PvP", Graphics::getGeneralButtonSize())) {
            current_state = state::PLAYER_VS_PLAYER;
            saved_state = current_state;
        }
        if (ImGui::Button("PvE", Graphics::getGeneralButtonSize())) {
            current_state = state::PLAYER_VS_CPU;
            saved_state = current_state;
        }
        if (ImGui::Button("Back to Lobby", Graphics::getGeneralButtonSize())) {
            subject.notify(event::BACK_TO_THE_GAME_CHOOSE);
        }
    }
    ImGui::End();
}

void PongScene::drawPause()
{
    bool opened = true;
    const Vector2 game_resolution = Graphics::getResolution();
    if (ImGui::Begin("Menu", &opened, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | 
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
        ImGui::SetWindowPos({game_resolution.x / 2.f - ImGui::GetWindowWidth() / 2.f, 
                             game_resolution.y / 2.f - ImGui::GetWindowHeight() / 2.f});
        ImGui::SetWindowFontScale(2.f);
        if (ImGui::Button("Continue", Graphics::getGeneralButtonSize()))
            current_state = saved_state;
        if (ImGui::Button("Back to game menu", Graphics::getGeneralButtonSize()))
            subject.notify(event::BACK_TO_THE_GAME_CHOOSE);
    }
    ImGui::End();
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
