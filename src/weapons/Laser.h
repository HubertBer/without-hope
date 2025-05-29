#pragma once

#include "Weapon.h"
#include "../GameData.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"

class Laser : public Weapon{
public:
    Laser();
    void gameUpdate(GameData& game, Player& player, float dt) override;
    void physicsUpdate(GameData& game, Player& player) override;

private:
    float bulletCooldown = 0.0f;
    float maxBulletCooldown = 2.0f;
};