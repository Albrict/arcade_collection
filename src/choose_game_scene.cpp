#include "choose_game_scene.hpp"
#include "graphics.hpp"

namespace {
    enum MenuButtons : size_t {
        PONG = 0,
        ARKANOID,
        SPACE_INVADERS,
        BACK_TO_MAIN_MENU
    };
};

ChooseGameScene::ChooseGameScene()
    : Scene()
{
    const std::array<const char*, 4> button_labels = {"Pong", "Arkanoid", "Spave Invaders", "Back to the main menu"};
    const float button_width = 215.f;
    const float button_height = 70.f;

    const int initial_x = Graphics::getResolution().x / 2 - button_width / 2;
    int initial_y = Graphics::getResolution().y / 3 - button_height;

    for (int i = 0; i < menu_buttons.size(); ++i) {
        menu_buttons[i] = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[i]);
        initial_y += button_height * 2;
    }
    auto pong_callback              = [](void *data){ Subject *subject = static_cast<Subject*>(data); subject->notify(event::GAME_PONG); };
    auto arkanoid_callback          = [](void *data){ Subject *subject = static_cast<Subject*>(data); subject->notify(event::GAME_ARKANOID); };
    auto space_invaders_callback    = [](void *data){ Subject *subject = static_cast<Subject*>(data); subject->notify(event::GAME_SPACE_INVADERS); };
    auto back_to_main_menu_callback = [](void *data){ Subject *subject = static_cast<Subject*>(data); subject->notify(event::BACK_TO_THE_MAIN_MENU); };

    menu_buttons[PONG]->setCallback(pong_callback, &this->subject);
    menu_buttons[ARKANOID]->setCallback(arkanoid_callback, &this->subject);
    menu_buttons[SPACE_INVADERS]->setCallback(space_invaders_callback, &this->subject);
    menu_buttons[BACK_TO_MAIN_MENU]->setCallback(back_to_main_menu_callback, &this->subject);
}
