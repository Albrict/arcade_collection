#pragma once
#include "scene.hpp"
#include "simple_button.hpp"

class MenuScene : public Scene {
public:
    MenuScene(); 
    ~MenuScene() = default;
private:
    unsigned int widget_table = 0;
};

