#include "menu_scene.hpp"
#include "graphics.hpp"

namespace {
    enum MenuButtons : size_t {
        PLAY_BUTTON = 0,
        EXIT_BUTTON
    };
}

MenuScene::MenuScene() 
    : Scene()
{
    const std::array<const char*, 3> button_labels = {"Play", "Exit"};
    const float button_width = 150.f;
    const float button_height = 70.f;
    const std::array<Widget::callback, 2> callback_array = {
        {
            { [](void *data){ std::any message = event::PLAY; MessageSystem::sendMessage(MessageSystem::root_scene_id, message); } },
            { [](void *data){ std::any message = event::EXIT; MessageSystem::sendMessage(MessageSystem::root_scene_id, message); } },
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
