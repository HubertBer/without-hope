#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../GameData.h"

struct SimpleBullet : public Entity {
public:
    SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> entity) override;
    void draw(float lerpValue) override;
    EntityType type() override;

    static constexpr float maxSpeed = 800.f;
    float hitboxRadius = 10.f;
};