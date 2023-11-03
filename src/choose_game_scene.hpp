#pragma once
#include "scene.hpp"
#include "simple_button.hpp"
#include <array>

class ChooseGameScene : public Scene {
public:
    ChooseGameScene();
    ~ChooseGameScene() = default; 
private:
    unsigned int widget_table = 0;
};
