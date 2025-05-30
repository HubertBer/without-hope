#pragma once

#include "Entity.h"
#include "../GameData.h"

class SlowCircle : public Entity{
public:
    SlowCircle(Collider collider);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void draw() override;
    EntityType type() override;

private:
    float radius=0.0f;
    const float expansionSpeed = 500.f;
    const float outlineWidth = 100;
    
};