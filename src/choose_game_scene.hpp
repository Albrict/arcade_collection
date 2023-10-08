#pragma once
#include "scene.hpp"
#include "simple_button.hpp"
#include <array>

class ChooseGameScene : public Scene {
public:
    ChooseGameScene();
    ~ChooseGameScene() = default; 

    void proccessEvents() override 
    { for (auto &button : menu_buttons) button->proccessEvents(); }
    void update() override
    { for (auto &button : menu_buttons) button->update(); }
    void draw() const override
    { for (auto &button : menu_buttons) button->draw(); }
private:
    std::array<SimpleButton::unique_ptr, 4> menu_buttons {};
};
