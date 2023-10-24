#include <algorithm>
#include <raylib.h>
#include <memory>
#include <algorithm>

#include "arkanoid_scene.hpp"
#include "choose_game_scene.hpp"
#include "game.hpp"
#include "menu_scene.hpp"
#include "pong_scene.hpp"
#include "graphics.hpp"

namespace Game {
    std::unique_ptr<Scene> current_scene;
    Observer scene_observer;

    bool running;

    void proccessEvents();
    void draw(RenderTexture2D target, const Vector2 resolution, const float scale);
    inline void changeSceneTo(Scene *new_scene);
};

void Game::init()
{
    // This is game resolution, not a physical one
    const Vector2 game_resolution = {1920.f, 1200.f};
    Graphics::setResolution(game_resolution);

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(game_resolution.x, game_resolution.y, "Arcade Collection");
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);
    ToggleFullscreen();
    
    current_scene = std::make_unique<MenuScene>();
    current_scene->subscripe(scene_observer);

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
        const float scale = std::min(GetScreenWidth() / game_resolution.x, GetScreenHeight() / game_resolution.y);
        proccessEvents();
        current_scene->update();
        draw(target, game_resolution, scale);
    }
    UnloadRenderTexture(target);
}

void Game::quit()
{
    CloseWindow();
}

void Game::proccessEvents()
{
    current_scene->proccessEvents();
    event event = scene_observer.getEvent();
    switch(event) {
    case event::NONE:
        return;
        break;
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
    case event::GAME_SPACE_INVADERS:
        ;
        break;
    default:
        break;
    }
}

void Game::draw(RenderTexture2D target, const Vector2 resolution, const float scale)
{
    const Rectangle source_rect = { 0.0f, 0.0f, 
                                    static_cast<float>(target.texture.width), 
                                    static_cast<float>(-target.texture.height) };

    const Rectangle dest_rect = {   (GetScreenWidth() - (resolution.x * scale)) * 0.5f, 
                                    (GetScreenHeight() - (resolution.y * scale))*0.5f,
                                    resolution.x * scale, resolution.y *scale };
    BeginTextureMode(target);
    {
        ClearBackground(BLACK);
        current_scene->draw(); 
    }
    EndTextureMode();

    BeginDrawing();
    {
        DrawTexturePro(target.texture, source_rect, dest_rect, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    EndDrawing();
}

inline void Game::changeSceneTo(Scene *new_scene)
{
    current_scene.reset(new_scene);
    current_scene->subscripe(scene_observer); 
}
