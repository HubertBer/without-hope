#pragma once

#include "Entity.h"
#include "../GameData.h"
#include "raylib.h"

class OutsideMapSpawner : public Entity{
public:
    OutsideMapSpawner(Vector2 delay);
    void gameUpdate(GameData& game, float dt) override;
    EntityType type() override;

    float timer = 0;
    Vector2 delay{5.f, 10.f};
    float pSquadron = .2f;
};