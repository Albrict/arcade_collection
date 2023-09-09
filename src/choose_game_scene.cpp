#include "choose_game_scene.hpp"
#include "graphics.hpp"

void ChooseGameScene::draw() noexcept
{
    const Vector2 game_resolution = Graphics::getResolution();
    if (ImGui::Begin("Menu", &opened, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | 
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
        ImGui::SetWindowPos({game_resolution.x / 2.f - ImGui::GetWindowWidth() / 2.f, 
                             game_resolution.y / 2.f - ImGui::GetWindowHeight() / 2.f});
        ImGui::SetWindowFontScale(2.f);
        if (ImGui::Button("Pong", button_size))
            subject.notify(event::GAME_PONG);
        if (ImGui::Button("Main menu", {200.f, 70.f}))
            subject.notify(event::BACK_TO_THE_MAIN_MENU);
        ImGui::End();
    }
}
