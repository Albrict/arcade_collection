#include <algorithm>
#include <raylib.h>
#include <memory>
#include <algorithm>

#include "game.hpp"
#include "menu_scene.hpp"
#include "choose_game_scene.hpp"
#include "pong_scene.hpp"
#include "arkanoid_scene.hpp"
#include "graphics.hpp"

#include "../third_party/imgui.h"
#include "../third_party/rlImGui.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))


Game::Game()
    : current_scene(),
    scene_observer(),
    running(true)
{
    
    const char *title = "Arcade collection";
    const bool dark_theme = true;
    const int FPS = 60;
    // This is game resolution, not a physical one
    const Vector2 game_resolution = {1920.f, 1200.f};
    Graphics::setResolution(game_resolution);

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(game_resolution.x, game_resolution.y, title);
    SetExitKey(KEY_NULL);
    rlImGuiSetup(dark_theme);
    SetTargetFPS(60);
    ToggleFullscreen();
    
    current_scene = std::make_unique<MenuScene>();
    current_scene->subscripe(scene_observer);
}

Game::~Game()
{
    rlImGuiShutdown();
    CloseWindow();
}

void Game::run()
{
    RenderTexture2D target;
    Vector2 game_resolution = Graphics::getResolution();
    target = LoadRenderTexture(game_resolution.x, game_resolution.y);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  
    while(running) {
        if (WindowShouldClose())
            running = false;
        game_resolution = Graphics::getResolution();
        const float scale = std::min(GetScreenWidth() / game_resolution.x, GetScreenHeight() / game_resolution.y);
        proccessEvents();
        current_scene->update();
        draw(target, game_resolution, scale);
    }
    UnloadRenderTexture(target);
}

void Game::draw(RenderTexture2D target, const Vector2 resolution, const float scale)
{
    const Rectangle source_rect = { 0.0f, 0.0f, 
                                    static_cast<float>(target.texture.width), 
                                    static_cast<float>(-target.texture.height) };

    const Rectangle dest_rect = {   (GetScreenWidth() - (resolution.x * scale)) * 0.5f, 
                                    (GetScreenHeight() - (resolution.y * scale))*0.5f,
                                    resolution.x * scale, resolution.y *scale };
    bool opened = true;
    BeginTextureMode(target);
    {
        ClearBackground(BLACK);
        rlImGuiBegin();
            current_scene->draw(); 
        rlImGuiEnd();
    }
    EndTextureMode();

    BeginDrawing();
    {
        DrawTexturePro(target.texture, source_rect, dest_rect, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    EndDrawing();
}

void Game::proccessEvents()
{
    current_scene->proccessEvents();
    event event = scene_observer.getEvent();
    switch(event) {
    case event::EXIT:
        running = false;
        break;
    case event::BACK_TO_THE_GAME_CHOOSE:
        changeSceneTo(new ChooseGameScene);
        break;
    case event::BACK_TO_THE_MAIN_MENU:
        changeSceneTo(new MenuScene);
        break;
    case event::PLAY:
        changeSceneTo(new ChooseGameScene);
        break;
    case event::GAME_PONG:
        changeSceneTo(new PongScene);
        break;
    case event::GAME_ARKANOID:
        changeSceneTo(new ArkanoidScene);
        break;
    default:
        break;
    }
}

void Game::changeSceneTo(Scene *new_scene)
{
    current_scene.reset(new_scene);
    current_scene->subscripe(scene_observer); 
}
