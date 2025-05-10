#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../GameData.h"

struct SimpleBullet : public Entity {
public:
    SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity, float rotation);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> entity,GameData& gameData) override;
    void draw() override;
    EntityType type() override;

    static constexpr float BASE_RADIUS =10.f;
    static constexpr float maxSpeed = 800.f;
    static constexpr float vanishDistance = 4000.f;
};