#include "settings_scene.hpp"
#include "graphics.hpp"
#include "../third_party/rlImGuiColors.h"

void SettingsScene::draw() noexcept
{
    const char *menu_name = "Menu";
    const Vector2 game_resolution = Graphics::getResolution();
    if (ImGui::Begin("Settings", &opened,  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove 
                     |  ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize)) {
        ImGui::SetWindowPos({game_resolution.x / 2.f - ImGui::GetWindowWidth() / 2.f, 
                             game_resolution.y / 3.f - ImGui::GetWindowHeight() / 2.f});
        ImGui::SetWindowFontScale(2.f);
        ImGui::Text("Resolution:");
//        if (ImGui::BeginCombo("Resolution", "Resolution", ImGuiComboFlags_HeightLargest)) {
//            ImGui::Selectable("1920x1200");
//            ImGui::Selectable("1600x1200");
//            ImGui::Selectable("1336x768");
//            ImGui::EndCombo();
//        }
        ImGui::End();
    }
}
