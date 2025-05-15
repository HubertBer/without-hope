#pragma once

#include "Entity.h"
#include "../GameData.h"

class ElectricFence : public Entity{
public:
    ElectricFence(Collider collider);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void draw() override;
    EntityType type() override;

private:
    const Color color = SKYBLUE;
    const float width = 10.0f;
};