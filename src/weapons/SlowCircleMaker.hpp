#pragma once

#include "Weapon.h"

class SlowCircleMaker : public Weapon{
public:
    SlowCircleMaker();
    void gameUpdate(GameData& game, Player& player, float dt) override;
    void physicsUpdate(GameData& game, Player& player) override;
    
    std::shared_ptr<Entity> slowCircle;
    float timer = 0.f;
    const float cooldown = 10.f;
};