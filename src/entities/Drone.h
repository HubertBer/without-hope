#pragma once

#include "Entity.h"
#include "raylib.h"

class Drone : public Entity {
public:
    Drone(Vector2 pos, float angle);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> other, GameData& gameData) override;
    void draw() override;
    EntityType type() override;

private:
    float angle = 0.f;
    Vector2 acceleration{0.f, 0.f};

    static constexpr Vector2 OFFSET{70.f, 0.f};
    static constexpr float BASE_RADIUS = 15.f;
    static constexpr float MAX_SPEED = 1200.f;
    static constexpr float MAX_ACCELERATION = 2000.f;
    static constexpr float ANGULAR_SPEED = 50.0f; 
    static constexpr Color color{GRAY};
};