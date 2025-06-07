#pragma once

#include "Entity.h"
#include "../GameData.h"
#include "../music/SoundLoader.h"
class LaserEntity : public Entity{
public:
    static constexpr float LASER_LENGTH = 2000.f;
    LaserEntity(Collider collider);
    void gameUpdate(GameData& game, float dt) override;
    void draw() override;
    EntityType type() override;

private:
    // Visual width, not the collider width
    const float width = 100.0f;
    float lifetime = 0.5f;

};