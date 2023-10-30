#include "pong_scene.hpp"
#include "graphics.hpp"
#include "simple_button.hpp"
#include "pong_player.hpp"
#include "pong_racket.hpp"
#include <iostream>

PongScene::PongScene()
    : Scene()
{
    menu_widget_table = Scene::createTable();
    pause_widget_table = Scene::createTable();
    pvp_mode_table = Scene::createTable();
    pve_mode_table = Scene::createTable();
    graphical_objects_table = Scene::createTable();
    initMenuWidgetsTable();
    initPauseWidgetsTable();
    initGraphicalObjectsTable();
}

void PongScene::proccessEvents()
{
    std::any data = MessageSystem::getMessage(Object::object_id);
    if (data.has_value()) {
        auto msg = std::any_cast<PongRacket::Message>(data);
        switch(msg) {
        case PongRacket::Message::FIRST_PLAYER_WIN:
            ++first_player_score;
            break;
        case PongRacket::Message::SECOND_PLAYER_WIN:
            ++second_player_score;
            break;
        }
    }
    if (current_table == pvp_mode_table || current_table == pve_mode_table) {
        if (IsKeyDown(KEY_ESCAPE)) {
            current_game_mode = current_table;
            current_table = pause_widget_table;
        }
    }
    Scene::proccessTable(graphical_objects_table);
    Scene::proccessTable(current_table);
}

void PongScene::update()
{
    Scene::updateTable(current_table);
}

void PongScene::draw() const 
{
    if (current_table == pause_widget_table) {
        Scene::drawTable(current_game_mode);
        Scene::drawTable(graphical_objects_table);
        Scene::drawTable(current_table);
    } else {
        if (current_table != menu_widget_table)
            Scene::drawTable(graphical_objects_table);
        Scene::drawTable(current_table);
    }
}

void PongScene::initMenuWidgetsTable()
{
    const Vector2 resolution = Graphics::getResolution();
    const std::array<const char*, 3> menu_button_labels = { "PvP", "PvE", "Back to lobby" };
    const float button_width = 215.f;
    const float button_height = 70.f;
    const std::array<Widget::callback, 3> menu_callbacks = {
        {
            { [](void *data) { auto scene = static_cast<PongScene*>(data); scene->current_table = scene->pvp_mode_table; scene->initPvpObjectsTable(); } },
            { [](void *data) { auto scene = static_cast<PongScene*>(data); scene->current_table = scene->pve_mode_table; scene->initPveObjectsTable(); } },
            { [](void *data) { auto msg = event::BACK_TO_THE_GAME_CHOOSE; MessageSystem::sendMessage(MessageSystem::root_scene_id, msg); } }
        }
    };

    const int initial_x = resolution.x / 2 - button_width / 2;
    int initial_y = resolution.y / 3 - button_height;
    {
        for (size_t i = 0; i < menu_callbacks.size(); ++i) {
            auto button = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, menu_button_labels[i]);
            button->setCallback(menu_callbacks[i], this);
            initial_y += button_height * 2;

            Scene::insertObject(std::move(button), menu_widget_table);
        }
    }
    current_table = menu_widget_table;
}

void PongScene::initPauseWidgetsTable()
{
    const Vector2 resolution = Graphics::getResolution();
    const std::array<const char*, 2> pause_button_labels = { "Continue", "Back to menu" };
    const float button_width = 215.f;
    const float button_height = 70.f;
    const std::array<Widget::callback, 2> pause_callback = {
        {
            { [](void *data) { auto scene = static_cast<PongScene*>(data); scene->current_table = scene->current_game_mode; } },
            { [](void *data) { auto scene = static_cast<PongScene*>(data); scene->current_table = scene->menu_widget_table; } },
        }
    };
    const int initial_x = resolution.x / 2 - button_width / 2;

    int initial_y = resolution.y / 3 - button_height;
    {
        for (size_t i = 0; i < pause_callback.size(); ++i) {
            auto button = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, pause_button_labels[i]);
            button->setCallback(pause_callback[i], this);
            initial_y += button_height * 2;
            Scene::insertObject(std::move(button), pause_widget_table);
        }
    }
}
    
void PongScene::initPvpObjectsTable()
{
    Scene::clearTable(pvp_mode_table);
    const Vector2 resolution = Graphics::getResolution();
    const float players_width = 10.f;
    const float players_height = 100.f;
    const Rectangle first_player = { .x = 30.f, .y = resolution.y / 2.f, .width = players_width, .height = players_height};
    const Rectangle second_player = { .x = resolution.x - 40.f, .y = resolution.y / 2.f, .width = players_width, .height = players_height };
    const Rectangle racket({Graphics::getResolution().x / 2.f, Graphics::getResolution().y / 2.f, 20.f, 20.f});
    {
        auto first_player_obj = std::make_unique<PongPlayer>(first_player, WHITE, PongPlayer::PlayerType::FIRST);
        auto second_player_obj = std::make_unique<PongPlayer>(second_player, WHITE, PongPlayer::PlayerType::SECOND);
        auto racket_obj = std::make_unique<PongRacket>(Object::object_id, first_player_obj->getObjectId(), second_player_obj->getObjectId(), racket, WHITE);
        Scene::insertObject(std::move(first_player_obj), pvp_mode_table);
        Scene::insertObject(std::move(second_player_obj), pvp_mode_table);
        Scene::insertObject(std::move(racket_obj), pvp_mode_table);
    }
}

void PongScene::initPveObjectsTable()
{
    Scene::clearTable(pve_mode_table);
    const Vector2 resolution = Graphics::getResolution();
    const float players_width = 10.f;
    const float players_height = 100.f;
    const Rectangle first_player = { .x = 30.f, .y = resolution.y / 2.f, .width = players_width, .height = players_height};
    const Rectangle second_player = { .x = resolution.x - 40.f, .y = resolution.y / 2.f, .width = players_width, .height = players_height };
    const Rectangle racket({Graphics::getResolution().x / 2.f, Graphics::getResolution().y / 2.f, 20.f, 20.f});
    {
        auto first_player_obj = std::make_unique<PongPlayer>(first_player, WHITE, PongPlayer::PlayerType::FIRST);
        auto second_player_obj = std::make_unique<PongPlayer>(second_player, WHITE, PongPlayer::PlayerType::CPU);
        auto racket_obj = std::make_unique<PongRacket>(Object::object_id, first_player_obj->getObjectId(), second_player_obj->getObjectId(), racket, WHITE);

        Scene::insertObject(std::move(first_player_obj), pve_mode_table);
        Scene::insertObject(std::move(second_player_obj), pve_mode_table);
        Scene::insertObject(std::move(racket_obj), pve_mode_table);
    }
}

void PongScene::initGraphicalObjectsTable()
{
    const float font_size = 54.f;
    const float middle_x = Graphics::getResolution().x / 2.f;
    const Vector2 first_label_pos = { middle_x - middle_x / 2.f, Graphics::getResolution().y / 4.f};
    const Vector2 second_label_pos = { middle_x + middle_x / 2.f, Graphics::getResolution().y / 4.f };
    const std::array<Widget::callback, 2> label_callbacks = {
        {
            { [this](void *data) { auto label = static_cast<Label*>(data); label->updateLabel(TextFormat("%d", first_player_score)); } },
            { [this](void *data) { auto label = static_cast<Label*>(data); label->updateLabel(TextFormat("%d", second_player_score)); } },
        }
    };
    {
        auto first_label = std::make_unique<Label>(first_label_pos, TextFormat("%d", first_player_score), GetFontDefault(), font_size);
        auto second_label = std::make_unique<Label>(second_label_pos, TextFormat("%d", second_player_score), GetFontDefault(), font_size);
        first_label->setCallback(label_callbacks[0], first_label.get());
        second_label->setCallback(label_callbacks[1], second_label.get());

        Scene::insertObject(std::move(first_label), graphical_objects_table);
        Scene::insertObject(std::move(second_label), graphical_objects_table);
        Scene::insertObject(std::make_unique<PongScene::MiddleLine>(), graphical_objects_table);
    }
}
