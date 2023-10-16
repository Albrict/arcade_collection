#pragma once
#include <raylib.h>
#include "scene.hpp"

class SettingsScene : public Scene {
public:
    SettingsScene() {}
    ~SettingsScene() {}

    void proccessEvents() {}
    void update() {}
    void draw() noexcept;
private:
    bool opened = true;
    Vector2 button_size = {200.f, 70.f};
};
