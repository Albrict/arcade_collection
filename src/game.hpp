#pragma once
#include <memory>
#include <raylib.h>
#include "scene.hpp"
class Game {
    std::unique_ptr<Scene> current_scene;
    Observer scene_observer;

    bool running;
public:
    Game();
    ~Game();

    void run();
private:
    void proccessEvents();
    void draw(RenderTexture2D target, const Vector2 resolution, const float scale);
    void changeSceneTo(Scene *new_scene);
};
