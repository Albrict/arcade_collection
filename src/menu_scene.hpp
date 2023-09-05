#pragma once
#include "scene.hpp"
#include "settings_scene.hpp"
#include "../third_party/imgui.h"

class MenuScene : public Scene {
public:
    MenuScene() {}
    ~MenuScene() {}

    void proccessEvents() {}
    void update() {}
    void draw() noexcept;
private:
    void drawMenu();
private:
    bool opened = true;
    ImVec2 button_size = {200.f, 70.f};

    enum class state {
        MAIN_MENU,
        SETTINGS
    };
    state current_state = state::MAIN_MENU;
    SettingsScene settings;
};
