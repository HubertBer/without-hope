#pragma once

#include "Weapon.h"
#include "../GameData.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"

class Minigun : public Weapon{
public:
    Minigun();
    void gameUpdate(GameData& game, Player& player, float dt) override;
    void physicsUpdate(GameData& game, Player& player) override;

private:
    float bulletCooldown = 0.05f;

    const float maxBulletCooldown = 0.15f;
    const float spreadAngle = 12.0f;
};