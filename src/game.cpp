#include <algorithm>
#include <raylib.h>
#include <memory>

#include "game.hpp"
#include "menu_scene.hpp"
#include "choose_game_scene.hpp"
#include "graphics.hpp"

#include "../third_party/imgui.h"
#include "../third_party/rlImGui.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))


namespace Game {
    int FPS = 60;
    std::unique_ptr<Scene> scene;
    Observer observer; 
    bool running = false; 
    void draw(RenderTexture2D target, Vector2 resolution, float scale);
    void proccessEvents();
};

void Game::init()
{
    const char *title = "Arcade collection";
    const bool dark_theme = true;
    // This is game resolution, not a physical one
    const Vector2 game_resolution = {1920.f, 1200.f};

    Graphics::setResolution(game_resolution);
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(game_resolution.x, game_resolution.y, title);
    rlImGuiSetup(dark_theme);
    SetTargetFPS(FPS);
    ToggleFullscreen();
    
    scene = std::make_unique<MenuScene>();
    scene->subscripe(observer);
    running = true;
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
        const float scale = MIN(GetScreenWidth() / game_resolution.x, GetScreenHeight() / game_resolution.y);
        proccessEvents();
        draw(target, game_resolution, scale);
    }
    UnloadRenderTexture(target);
}

void Game::quit()
{
    rlImGuiShutdown();
    CloseWindow();
}

void Game::draw(RenderTexture2D target, Vector2 resolution, float scale)
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
        ClearBackground(WHITE);
        rlImGuiBegin();
            scene->draw(); 
        rlImGuiEnd();
    }
    EndTextureMode();

    BeginDrawing();
    {
        ClearBackground(BLACK);
        DrawTexturePro(target.texture, source_rect, dest_rect, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    EndDrawing();
}

void Game::proccessEvents()
{
    event event = observer.getEvent();
    switch(event) {
    case event::EXIT:
        running = false;
        break;
    case event::PLAY:
        scene.reset();
        scene = std::make_unique<ChooseGameScene>();
        break;
    default:
        break;
    }
}
