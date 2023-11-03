#include "game.hpp"
#include "main_scene.hpp"

int main (int argc, char *argv[]) 
{
//    Game::init();
//    Game::run();
//    Game::quit();
    auto scene = std::make_unique<MainScene>();
    scene->run();
}
