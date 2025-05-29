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
    void shootAt(GameData& game, std::shared_ptr<Entity> enem);

    float angle = 0.f;
    float timer = 0.f;

    static constexpr Vector2 OFFSET{70.f, 0.f};
    static constexpr float BASE_RADIUS = 15.f;
    static constexpr float MAX_SPEED = 560.f;
    static constexpr float MAX_ACCELERATION = 2000.f;
    static constexpr float ANGULAR_SPEED = 50.0f; 
    static constexpr Color color{GRAY};

    static constexpr float COOLDOWN = 7.f;
    static constexpr float RANGE = 800.f;
};