#pragma once
#include "scene.hpp"
#include "settings_scene.hpp"
#include "../third_party/imgui.h"

class MenuScene : public Scene {
    enum class state {
        MAIN_MENU,
        SETTINGS
    };
    bool opened = true;
    state current_state = state::MAIN_MENU;
    SettingsScene settings;
public:
    MenuScene() {}
    ~MenuScene() {}

    void proccessEvents() {}
    void update() {}
    void draw() noexcept;
private:
    void drawMenu();
};
