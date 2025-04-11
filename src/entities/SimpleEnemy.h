#pragma once

#include <raylib.h>

#include "Entity.h"

class SimpleEnemy : public Entity{
public:
    SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> entity) override;
    void draw(float lerpValue) override;
    EntityType type() override;

    float hitboxRadius = 10.0f;

private:
    static constexpr float maxSpeed = 300.f;
    
};