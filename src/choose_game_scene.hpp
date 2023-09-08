#pragma once
#include "scene.hpp"
#include "../third_party/imgui.h"

class ChooseGameScene : public Scene {
    bool opened = true;
public:
    ChooseGameScene() {}
    ~ChooseGameScene() {}

    void proccessEvents() {}
    void update() {}
    void draw() noexcept;
};
