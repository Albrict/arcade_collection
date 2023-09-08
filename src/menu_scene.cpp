#include "menu_scene.hpp"
#include "graphics.hpp"

void MenuScene::draw() noexcept
{
    switch(current_state) {
    case state::MAIN_MENU:
        drawMenu();
        break;
    case state::SETTINGS:
        settings.draw();
        break;
    }
}


void MenuScene::drawMenu()
{
    const Vector2 game_resolution = Graphics::getResolution();
    if (ImGui::Begin("Menu", &opened, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | 
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
        ImGui::SetWindowPos({game_resolution.x / 2.f - ImGui::GetWindowWidth() / 2.f, 
                             game_resolution.y / 2.f - ImGui::GetWindowHeight() / 2.f});
        ImGui::SetWindowFontScale(2.f);
        if (ImGui::Button("Play", Graphics::getGeneralButtonSize()))
            subject.notify(event::PLAY);
        if (ImGui::Button("Settings", Graphics::getGeneralButtonSize()))
            current_state = state::SETTINGS;
        if (ImGui::Button("Exit", Graphics::getGeneralButtonSize()))
            subject.notify(event::EXIT);
    }
    ImGui::End();
}
