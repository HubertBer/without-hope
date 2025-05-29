#pragma once

#include "Entity.h"
#include "../GameData.h"

class LaserEntity : public Entity{
public:
    LaserEntity(Collider collider);
    void gameUpdate(GameData& game, float dt) override;
    void draw() override;
    EntityType type() override;

private:
    // Visual width, not the collider width
    const float width = 100.0f;
    float lifetime = 0.5f;

};