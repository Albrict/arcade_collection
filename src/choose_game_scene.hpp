#pragma once
#include "scene.hpp"
#include "../third_party/imgui.h"

class ChooseGameScene : public Scene {
    bool opened = true;
    const ImVec2 button_size = {200.f, 70.f};
public:
    ChooseGameScene() = default; 
    ~ChooseGameScene() = default; 

    void proccessEvents() {}
    void update() {}
    void draw() noexcept;
};
