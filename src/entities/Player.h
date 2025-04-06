#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../GameData.h"

struct Player : public Entity{
public:
    Player(Vector2 prevPos, Vector2 pos, Vector2 velocity);
    void physicsUpdate(GameData& game) override;
    void gameUpdate(GameData& game, float dt) override;
    void draw(float lerpValue) override;
    EntityType type() override;

    static constexpr float maxSpeed = 500.0f;
};