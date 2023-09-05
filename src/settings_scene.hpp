#pragma once
#include "scene.hpp"
#include "../third_party/imgui.h"

class SettingsScene : public Scene {
public:
    SettingsScene() {}
    ~SettingsScene() {}

    void proccessEvents() {}
    void update() {}
    void draw() noexcept;
private:
    bool opened = true;
    ImVec2 button_size = {200.f, 70.f};
};
