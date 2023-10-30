#pragma once
#include "graphics.hpp"
#include "scene.hpp"

class PongScene : public Scene {
public:
    PongScene();
    ~PongScene() = default;

    void proccessEvents() override;
    void update() override;
    void draw() const override;
private:
    void initMenuWidgetsTable();
    void initPauseWidgetsTable();
    void initPvpObjectsTable();
    void initPveObjectsTable();
    void initGraphicalObjectsTable();
private:
    struct MiddleLine : public Object {
    public:
        void proccessEvents() override {}
        void update() override {}
        void draw() const override 
        { 
            const float font_size = 54.f;
            const float middle_x = Graphics::getResolution().x / 2.f;

            DrawLine(middle_x, 0.f, middle_x, Graphics::getResolution().y, WHITE);
        }
    };

    enum class State {
        MENU,
        PAUSE,
        GAME
    };
    State current_state = State::MENU;
    
    // Tables
    unsigned int current_table = 0;
    unsigned int menu_widget_table = 0;
    unsigned int pause_widget_table = 0;
    unsigned int pvp_mode_table = 0;
    unsigned int pve_mode_table = 0;
    unsigned int graphical_objects_table = 0;
    unsigned int current_game_mode = 0;
    // Scene properties
    unsigned int first_player_score = 0;
    unsigned int second_player_score = 0;

    // Scene objects 
    unsigned int first_player_score_label = 0;
    unsigned int second_player_score_label = 0;
};
