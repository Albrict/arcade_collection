#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include "arkanoid_scene.hpp"
#include "brick.hpp"
#include "graphics.hpp"
#include "collision.hpp"
#include "../third_party/cista.h"
#include "shapes.hpp"
#include "soft_brick.hpp"
#include "middle_brick.hpp"
#include "hard_brick.hpp"
#include "destroyed_brick.hpp"

namespace {
    using namespace std::filesystem;
    const int BRICK_AMOUNT  = 15;
    const path level_one_path    = "../assets/arkanoid_levels/level_one.data";
    const path level_two_path    = "../assets/arkanoid_levels/level_two.data";
    const path level_three_path  = "../assets/arkanoid_levels/level_three.data";
    const path choosen_level;

    enum LevelMenuButtons : size_t {
        LEVEL_ONE,
        LEVEL_TWO,
        LEVEL_THREE,
        BACK_TO_LOBBY
    };
}

ArkanoidScene::ArkanoidScene()
    : Scene(),
    ball_active(false),
    player({Graphics::getResolution().x / 2.f, Graphics::getResolution().y / 2.f + Graphics::getResolution().y / 4.f, 200.f, 20.f}),
    ball(),
    current_state(state::LEVEL_MENU),
    bricks(),
    level_menu_buttons(),
    pause_buttons()
{
    const Rectangle brick_rect({0.f, 0.f, Graphics::getResolution().x / BRICK_AMOUNT, 20.f});
    const Vector2 ball_pos = {player.x + player.width / 2.f, player.y - player.height};
    const Vector2 ball_velocity = {0.f, -10.f};
    ball = std::make_unique<Shapes::Circle>(ball_pos, ball_velocity, 10.f);
    
    const float button_width = 250.f;
    const float button_height = 70.f;

    const int initial_x = Graphics::getResolution().x / 2 - button_width / 2;
    int initial_y = Graphics::getResolution().y / 3 - button_height;
    
    const std::array<const char *, 6> button_labels = {"Level 1", "Level 2", "Level 3", "Back to Lobby", "Continue", "Back to level menu"};

    for (int i = 0; i < level_menu_buttons.size(); ++i) {
        level_menu_buttons[i] = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[i]);
        initial_y += button_height * 2;
    }
    auto first_level            = [](void *data){ ArkanoidScene *scene = static_cast<ArkanoidScene*>(data); scene->loadLevel(level_one_path); scene->current_state = state::GAME; };
    auto second_level           = [](void *data){ ArkanoidScene *scene = static_cast<ArkanoidScene*>(data); scene->loadLevel(level_two_path); scene->current_state = state::GAME; };
    auto third_level            = [](void *data){ ArkanoidScene *scene = static_cast<ArkanoidScene*>(data); scene->loadLevel(level_three_path); scene->current_state = state::GAME;};
    auto back_to_lobby_callback = [](void *data){ Subject *subject = static_cast<Subject*>(data); subject->notify(event::BACK_TO_THE_GAME_CHOOSE); };

    level_menu_buttons[LEVEL_ONE]->setCallback(first_level, this);
    level_menu_buttons[LEVEL_TWO]->setCallback(second_level, this);
    level_menu_buttons[LEVEL_THREE]->setCallback(third_level, this);
    level_menu_buttons[BACK_TO_LOBBY]->setCallback(back_to_lobby_callback, &this->subject);

    auto continue_callback      = [](void *data){ ArkanoidScene *scene = static_cast<ArkanoidScene*>(data); scene->current_state = state::GAME; };
    auto back_to_level_menu     = [](void *data){ ArkanoidScene *scene = static_cast<ArkanoidScene*>(data); scene->current_state = state::LEVEL_MENU; };

    initial_y = Graphics::getResolution().y / 3 - button_height;
    pause_buttons[0] = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[4]);
    initial_y += button_height * 2;
    pause_buttons[1] = std::make_unique<SimpleButton>(initial_x, initial_y, button_width, button_height, button_labels[5]);

    pause_buttons[0]->setCallback(continue_callback, this);
    pause_buttons[1]->setCallback(back_to_level_menu, this);
}

void ArkanoidScene::proccessEvents() 
{
    if (current_state == state::LEVEL_MENU) {
        for (auto &button : level_menu_buttons)
             button->proccessEvents();
    } else if (current_state == state::PAUSE) {
        for (auto &button : pause_buttons)
             button->proccessEvents();
    } else {
        if (IsKeyDown(KEY_ESCAPE)) {
            current_state = state::PAUSE;
        }
        if (IsKeyDown(KEY_A)) {
            if (!ball_active)
                ball_active = true;
            player.x -= 10.f;
            Collision::checkRecBoundsAndLimit(player);
        } 
        if (IsKeyDown(KEY_D)) {
            if (!ball_active)
                ball_active = true;
            player.x += 10.f;
            Collision::checkRecBoundsAndLimit(player);   
        }
        if (IsKeyDown(KEY_SPACE)) {
            ball_active = true;
        }
    }
}

void ArkanoidScene::update() 
{   
    if (current_state == state::GAME) {
        ball->position = Vector2Add(ball->position, ball->velocity); 
        checkPlayerCollisionWithBall();
        checkBallCollisionAndBounce();
        for (auto &row : bricks) {
            for (auto &brick : row) {
                if (brick->getBrickType() != Brick::brickType::DESTROYED) {
                    checkCollisionWithBrick(brick.get());
                    if (brick->getHealth() == 0)
                        brick.reset(new DestroyedBrick(brick->getBrickRect()));
                }
                brick->update();
            }
        }
    }
}

void ArkanoidScene::draw() const 
{
    switch(current_state) {
    case state::LEVEL_MENU:
        for (const auto &button : level_menu_buttons)
             button->draw();
        break;
    case state::PAUSE:
        for (const auto &button : pause_buttons) 
             button->draw();
        [[fallthrough]];
    default:
        for (const auto &row : bricks) {
            for (const auto &brick : row)
                brick->draw();
        }
        DrawRectangleRec(player, RED);
        DrawCircle(ball->position.x, ball->position.y, ball->radius, WHITE);
    }
}

void ArkanoidScene::checkCollisionWithBrick(Brick *brick)
{
    const Rectangle brick_rect = brick->getBrickRect();
    // Hit below
    if (((ball->position.y - ball->radius) <= (brick_rect.y + brick_rect.height / 2)) &&
        ((ball->position.y - ball->radius) > (brick_rect.y + brick_rect.height / 2 + ball->velocity.y)) &&
        ((fabs(ball->position.x - brick_rect.x)) < (brick_rect.width /2 + ball->radius*2/3)) && (ball->velocity.y < 0))
    {
        brick->damageBrick();
        ball->velocity.y *= -1;
    }
    // Hit above
    else if (((ball->position.y + ball->radius) >= (brick_rect.y - brick_rect.height / 2)) &&
            ((ball->position.y + ball->radius) < (brick_rect.y - brick_rect.height / 2 + ball->velocity.y)) &&
            ((fabs(ball->position.x - brick_rect.x)) < (brick_rect.width /2 + ball->radius*2/3)) && (ball->velocity.y > 0))
    {
        brick->damageBrick();
        ball->velocity.y *= -1;
    }
    // Hit left
    else if (((ball->position.x + ball->radius) >= (brick_rect.x - brick_rect.width / 2)) &&
            ((ball->position.x + ball->radius) < (brick_rect.x - brick_rect.width / 2 + ball->velocity.x)) &&
            ((fabs(ball->position.y - brick_rect.y)) < (brick_rect.height /2 + ball->radius*2/3)) && (ball->velocity.x > 0))
    {
        brick->damageBrick();
        ball->velocity.y *= -1;
    }
    // Hit right
    else if (((ball->position.x - ball->radius) <= (brick_rect.x + brick_rect.width / 2)) &&
            ((ball->position.x - ball->radius) > (brick_rect.x + brick_rect.width / 2 + ball->velocity.x)) &&
            ((fabs(ball->position.y - brick_rect.y)) < (brick_rect.height /2 + ball->radius*2/3)) && (ball->velocity.x < 0))
    {
        brick->damageBrick();
        ball->velocity.y *= -1;
    }
}

std::unique_ptr<Brick> ArkanoidScene::createBrickFrom(const Brick::brickType type, const Rectangle rect)
{
    switch(type) {
    case Brick::brickType::SOFT:
        return std::make_unique<SoftBrick>(rect);
    case Brick::brickType::MIDDLE:
        return std::make_unique<MiddleBrick>(rect);
    case Brick::brickType::HARD:
        return std::make_unique<HardBrick>(rect);
    case Brick::brickType::DESTROYED:
        return std::make_unique<DestroyedBrick>(rect);
    }
}

void ArkanoidScene::checkBallCollisionAndBounce()
{
    if (ball->position.x + ball->radius >= Graphics::getResolution().x) {
        ball->position.x -= ball->radius;
        ball->velocity.x *= -1;
    } else if (ball->position.x - ball->radius <= 0) {
        ball->position.x += ball->radius;
        ball->velocity.x *= -1;
    } else if (ball->position.y + ball->radius >= Graphics::getResolution().y) {
        ball->position.y -= ball->radius;
        ball->velocity.y *= -1;
    }
    else if (ball->position.y - ball->radius  <= 0) {
        ball->position.y += ball->radius;
        ball->velocity.y *= -1;
    }
}

void ArkanoidScene::checkPlayerCollisionWithBall()
{
    if (CheckCollisionCircleRec(ball->position, ball->radius, player)) {
        if (ball->velocity.y < 0 || ball->velocity.y > 0 || ball->velocity.x < 0 || ball->velocity.x > 0) {
            ball->velocity.y *= -1;
            ball->velocity.x = (ball->position.x - player.x) / (player.width / 2) * 10.f;
            // Limit speed
            if (ball->velocity.x >= 200.f)
                ball->velocity.x = 200.f;
            if (ball->velocity.x <= -200.f)
                ball->velocity.x = -200.f;

            if (ball->velocity.y >= 200.f)
                ball->velocity.y = 200.f;
            if (ball->velocity.y == -200.f)
                ball->velocity.y = -200.f;
        }
    }
}


void ArkanoidScene::loadLevel(const path &path)
{
    bricks.clear();
    const Rectangle brick_rect({0.f, 0.f, Graphics::getResolution().x / BRICK_AMOUNT, 20.f});
    using data_vector = cista::raw::vector<cista::raw::vector<Brick::brickType>>;
    // Load level
    std::ifstream input(path, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    // Deserialize it
    auto level_data = cista::deserialize<data_vector>(buffer);
    if (bricks.size() != level_data->size()) {
        bricks.resize(level_data->size());
        for (auto &row : bricks) 
            row.resize(level_data->at(0).size());
    }

    Rectangle brick = brick_rect;
    for (size_t i = 0; i < bricks.size(); ++i) {
        for (size_t j = 0; j < bricks[i].size(); ++j) {
            bricks[i][j] = createBrickFrom(level_data->at(i).at(j), brick);
            brick.x += brick_rect.width;
        }
        brick.x = 0.f;
        brick.y += brick_rect.height;
    }
}
