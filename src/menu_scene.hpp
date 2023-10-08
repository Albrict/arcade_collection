#pragma once
#include "scene.hpp"
#include "simple_button.hpp"

class MenuScene : public Scene {
public:
    MenuScene(); 
    ~MenuScene() = default;

    void proccessEvents() override;
    void update() override;
    void draw() const override;
private:
    void drawMainMenu() const
    { for (const auto &button : main_menu_buttons) button->draw(); }
    void drawSettingsMenu() const
    { for (const auto &widget : settings_menu_widgets) widget->draw(); }
private:
    enum class States {
        MAIN_MENU,
        SETTINS_MENU
    };
    States current_state = States::MAIN_MENU;
    std::array<SimpleButton::unique_ptr, 3> main_menu_buttons {};
    std::array<Widget::unique_ptr, 3> settings_menu_widgets {};
};

