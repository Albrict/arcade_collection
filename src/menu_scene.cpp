#include "menu_scene.hpp"
#include "graphics.hpp"

namespace {
    enum MenuButtons : size_t {
        PLAY_BUTTON = 0,
        SETTINGS_BUTTON,
        EXIT_BUTTON
    };
}

MenuScene::MenuScene() 
    : Scene()
{
    const std::array<const char*, 3> button_labels = {"Play", "Settings", "Exit"};
    const float button_width = 150.f;
    const float button_height = 70.f;

    const int initial_x = Graphics::getResolution().x / 2 - button_width / 2;
    int initial_y = Graphics::getResolution().y / 3 - button_height;

    for (int i = 0; i < main_menu_buttons.size(); ++i) {
        main_menu_buttons[i] = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[i]);
        initial_y += button_height * 2;
    }
    auto play_callback = [](void *data){ Subject *subject = static_cast<Subject*>(data); subject->notify(event::PLAY); };
    auto exit_callback = [](void *data){ Subject *subject = static_cast<Subject*>(data); subject->notify(event::EXIT); };
    main_menu_buttons[PLAY_BUTTON]->setCallback(play_callback, &this->subject);
    main_menu_buttons[EXIT_BUTTON]->setCallback(exit_callback, &this->subject);
}

void MenuScene::proccessEvents()
{
    for (auto &button : main_menu_buttons)
        button->proccessEvents();
}

void MenuScene::update()
{
    for (auto &button : main_menu_buttons)
        button->update();
}

void MenuScene::draw() const 
{
    switch(current_state) {
    case States::MAIN_MENU:
        drawMainMenu();
        break;
    case States::SETTINS_MENU:
        drawSettingsMenu();
        break;
    }
}
