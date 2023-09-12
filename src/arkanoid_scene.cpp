#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <stdexcept>
#include "arkanoid_scene.hpp"
#include "graphics.hpp"
#include "collision.hpp"

namespace {
    const float SPACING = 10.f;
    const int BRICK_AMOUNT = 15;
}

ArkanoidScene::Brick::Brick(const brickType type, const Rectangle brick_rect)
    : type(type), brick_rect(brick_rect)
{
    assert((type != brickType::DESTROYED) && "Brick can't be initialized as destroyed!");
    switch(type) {
    case brickType::SOFT:
        color =  GREEN;
        break;
    case brickType::MIDDLE:
        color =  YELLOW;
        break;
    case brickType::HARD:
        color =  RED;
        break;
    default:
        break;
    }
}

ArkanoidScene::ArkanoidScene()
    : bricks(),
    brick_rect({0.f, 0.f, Graphics::getResolution().x / BRICK_AMOUNT - SPACING, 20.f}),
    player({Graphics::getResolution().x / 2.f, Graphics::getResolution().y / 2.f + Graphics::getResolution().y / 4.f, 200.f, 20.f}),
    ball({player.x + player.width / 2.f, player.y - player.height}, {0.f, -10.f}, 15.f)
{
    for (auto &row : bricks) 
        row.resize(BRICK_AMOUNT);

    Rectangle brick = brick_rect;
    for (size_t i = 0; i < bricks.size(); ++i) {
        for (size_t j = 0; j < bricks[i].size(); ++j) {
            bricks[i][j] = std::make_unique<Brick>(brickType::SOFT, brick);
            brick.x += brick_rect.width + SPACING;
        }
        brick.x = 0.f;
        brick.y += brick_rect.height + SPACING;
    }
}

void ArkanoidScene::proccessEvents() 
{
    if (IsKeyDown(KEY_A)) {
        if (!ball.active)
            ball.active = true;
        player.x -= 10.f;
        Collision::checkRecBoundsAndLimit(player);
    } 
    if (IsKeyDown(KEY_D)) {
        if (!ball.active)
            ball.active = true;
        player.x += 10.f;
        Collision::checkRecBoundsAndLimit(player);   
    }
    if (IsKeyDown(KEY_SPACE)) {
        ball.active = true;
    }
}

void ArkanoidScene::update() 
{
    if (ball.active) {
        ball.position = Vector2Add(ball.position, ball.velocity); 
        checkCollision();
    }
}

void ArkanoidScene::draw() noexcept
{
    for (const auto &row : bricks) {
        for (const auto &brick : row) {
            if (brick->type != brickType::DESTROYED) 
                DrawRectangleRec(brick->brick_rect, brick->color);
        }
    }
    DrawRectangleRec(player, RED);
    DrawCircle(ball.position.x, ball.position.y, ball.radius, WHITE);
}

void ArkanoidScene::checkCollision()
{
    if (((ball.position.x + ball.radius) >= Graphics::getResolution().x) || ((ball.position.x - ball.radius) <= 0)) 
        ball.velocity.x *= -1;
    if ((ball.position.y - ball.radius) <= 0) 
        ball.velocity.y *= -1;
    if ((ball.position.y + ball.radius) >= Graphics::getResolution().y)
    {
        ;
    }

    if (CheckCollisionCircleRec(ball.position, ball.radius,
        (Rectangle){ player.x - player.width /2, player.y - player.height / 2, player.x, player.y}))
    {
        if (ball.velocity.y > 0)
        {
            ball.velocity.y *= -1;
            ball.velocity.x = (ball.position.x - player.x)/(player.width / 2) * 5;
        }
    }

    for (size_t i = 0; i < bricks.size(); ++i) {
        for (size_t j = 0; j < bricks[i].size(); ++j) {
            if (bricks[i][j]->type != brickType::DESTROYED) {
                if (((ball.position.y - ball.radius) <= (bricks[i][j]->brick_rect.y + bricks[i][j]->brick_rect.height /2)) &&
                    ((ball.position.y - ball.radius) > (bricks[i][j]->brick_rect.y + bricks[i][j]->brick_rect.height / 2 + ball.velocity.y)) &&
                    ((fabs(ball.position.x - bricks[i][j]->brick_rect.x)) < (bricks[i][j]->brick_rect.width / 2 + ball.radius*2/3)) && (ball.velocity.y < 0))
                {
                    bricks[i][j]->type = brickType::DESTROYED;
                    ball.velocity.y *= -1;
                }
                // Hit above
                else if (((ball.position.y + ball.radius) >= (bricks[i][j]->brick_rect.y - bricks[i][j]->brick_rect.height /2)) &&
                        ((ball.position.y + ball.radius) < (bricks[i][j]->brick_rect.y - bricks[i][j]->brick_rect.height /2 + ball.velocity.y)) &&
                        ((fabs(ball.position.x - bricks[i][j]->brick_rect.x)) < (bricks[i][j]->brick_rect.width /2 + ball.radius*2/3)) && (ball.velocity.y > 0))
                {
                    bricks[i][j]->type = brickType::DESTROYED;
                    ball.velocity.y *= -1;
                }
                // Hit left
                else if (((ball.position.x + ball.radius) >= (bricks[i][j]->brick_rect.x - bricks[i][j]->brick_rect.width / 2)) &&
                        ((ball.position.x + ball.radius) < (bricks[i][j]->brick_rect.x - bricks[i][j]->brick_rect.width /2 + ball.velocity.x)) &&
                        ((fabs(ball.position.y - bricks[i][j]->brick_rect.y)) < (bricks[i][j]->brick_rect.height /2 + ball.radius*2/3)) && (ball.velocity.x > 0))
                {
                    bricks[i][j]->type = brickType::DESTROYED;
                    ball.velocity.x *= -1;
                }
                // Hit right
                else if (((ball.position.x - ball.radius) <= (bricks[i][j]->brick_rect.x + bricks[i][j]->brick_rect.width /2)) &&
                        ((ball.position.x - ball.radius) > (bricks[i][j]->brick_rect.x + bricks[i][j]->brick_rect.width /2 + ball.velocity.x)) &&
                        ((fabs(ball.position.y - bricks[i][j]->brick_rect.y)) < (bricks[i][j]->brick_rect.height /2 + ball.radius*2/3)) && (ball.velocity.x < 0))
                {
                    bricks[i][j]->type = brickType::DESTROYED;
                    ball.velocity.x *= -1;
                }
            }
        }
    }
}
