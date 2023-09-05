#pragma once
#include "scene.hpp"
#include "../third_party/imgui.h"

class ChooseGameScene : public Scene {
public:
    ChooseGameScene() {}
    ~ChooseGameScene() {}

    void proccessEvents() {}
    void update() {}
    void draw() noexcept;
private:
    bool opened = true;
    ImVec2 button_size = {200.f, 70.f};
};
