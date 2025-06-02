#pragma once

#include "Weapon.h"
#include "../GameData.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"

class Cannon : public Weapon{
public:
    Cannon();
    void gameUpdate(GameData& game, Player& player, float dt) override;
    void physicsUpdate(GameData& game, Player& player) override;
    WeaponName getWeaponName() override { return WeaponName::CANNON; }

private:
    float bulletCooldown = 0.0f;
    float maxBulletCooldown = 0.5f;
};