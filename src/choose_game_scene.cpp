#include "choose_game_scene.hpp"
#include "graphics.hpp"

ChooseGameScene::ChooseGameScene()
    : Scene()
{
    const std::array<const char*, 4> button_labels = {"Pong", "Arkanoid", "Spave Invaders", "Back to the main menu"};
    const float button_width = 215.f;
    const float button_height = 70.f;
    const std::array<Widget::callback, 4> callback_array = {
        {
            { [](void *data){ auto msg = event::GAME_PONG; MessageSystem::sendMessage(MessageSystem::root_scene_id, msg); } },
            { [](void *data){ auto msg = event::GAME_ARKANOID; MessageSystem::sendMessage(MessageSystem::root_scene_id, msg); } },
            { [](void *data){ auto msg = event::GAME_SPACE_INVADERS; MessageSystem::sendMessage(MessageSystem::root_scene_id, msg); } },
            { [](void *data){ auto msg = event::BACK_TO_THE_MAIN_MENU; MessageSystem::sendMessage(MessageSystem::root_scene_id, msg); } }
        }
    };

    const int initial_x = Graphics::getResolution().x / 2 - button_width / 2;
    int initial_y = Graphics::getResolution().y / 3 - button_height;
    
    widget_table = Scene::createTable();
    for (int i = 0; i < callback_array.size(); ++i) {
        auto button = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[i]);
        button->setCallback(callback_array[i], nullptr); 
        Scene::insertObject(std::move(button), widget_table);
        initial_y += button_height * 2;
    }
    Scene::setTableProccessing(widget_table, true);
}
