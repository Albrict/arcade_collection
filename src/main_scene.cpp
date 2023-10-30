#include "main_scene.hpp"
#include "graphics.hpp"
#include "menu_scene.hpp"
#include "choose_game_scene.hpp"
#include "object.hpp"
#include "pong_scene.hpp"
#include "arkanoid_scene.hpp"

MainScene::MainScene()
    : Scene()
{
    // This is game resolution, not a physical one
    const Vector2 game_resolution = {1920.f, 1200.f};
    Graphics::setResolution(game_resolution);

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(game_resolution.x, game_resolution.y, "Arcade Collection");
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);
    ToggleFullscreen();
    
    scene_table = Scene::createTable();
    auto menu_scene = std::make_unique<MenuScene>();
    current_scene = Scene::insertObject(std::move(menu_scene), scene_table);
    Scene::setTableProccessing(scene_table, true);

    resolution = Graphics::getResolution();
    target = LoadRenderTexture(game_resolution.x, game_resolution.y);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);  
}

void MainScene::run()
{
    while (running) {
        if (WindowShouldClose())
            running = false;
        proccessEvents();
        update();
        draw();
    }
}

void MainScene::proccessEvents()
{
    Scene::proccessEvents();
    std::any data = MessageSystem::getMessage(Object::object_id);
    if (data.has_value()) {
        enum event event = std::any_cast<enum event>(data); 
        switch(event) {
        case event::NONE:
            return;
            break;
        case event::EXIT:
            running = false;
            break;
        case event::PLAY:
            changeSceneTo(std::make_unique<ChooseGameScene>());
            break;
        case event::BACK_TO_THE_GAME_CHOOSE:
            changeSceneTo(std::make_unique<ChooseGameScene>());
            break;
        case event::BACK_TO_THE_MAIN_MENU:
            changeSceneTo(std::make_unique<MenuScene>());
            break;
        case event::GAME_PONG:
            changeSceneTo(std::make_unique<PongScene>());
            break;
        case event::GAME_ARKANOID:
            changeSceneTo(std::make_unique<ArkanoidScene>());
            break;
        case event::GAME_SPACE_INVADERS:
            ;
            break;
        default:
            break;
        }
    }
}

void MainScene::update()
{
    Scene::update();
    resolution = Graphics::getResolution();
    scale = std::min(GetScreenWidth() / resolution.x, GetScreenHeight() / resolution.y);
}

void MainScene::draw() const 
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
        Scene::draw();
    }
    EndTextureMode();

    BeginDrawing();
    {
        DrawTexturePro(target.texture, source_rect, dest_rect, (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    EndDrawing();
}
