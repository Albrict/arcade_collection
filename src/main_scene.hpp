#pragma once
#include "scene.hpp"
#include <raylib.h>
#include <stdexcept>

class MainScene : public Scene {
public:
    MainScene();
    ~MainScene()
    { CloseWindow(); }

    void run();
private:
    void proccessEvents() override;
    void update() override;
    void draw() const override;

    void changeSceneTo(std::unique_ptr<Scene> scene)
    {
        Scene::eraseObject(current_scene, scene_table);
        current_scene = Scene::insertObject(std::move(scene), scene_table);
    }
private:
    float scale = 0.f;
    Vector2 resolution {};
    RenderTexture2D target {};
    Observer scene_observer {};
    unsigned int scene_table = 0;
    unsigned int current_scene = 0;
    bool running = true;
};
