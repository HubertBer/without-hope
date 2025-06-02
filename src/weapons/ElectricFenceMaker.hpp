#pragma once

#include "Weapon.h"

class ElectricFenceMaker : public Weapon{
public:
    ElectricFenceMaker();
    void gameUpdate(GameData& game, Player& player, float dt) override;
    void physicsUpdate(GameData& game, Player& player) override;
    WeaponName getWeaponName() override { return WeaponName::ELECTRIC_FENCE; }

    std::shared_ptr<Entity> electricFence;
    bool placing = false;
    float timer = 0.f;
    const float cooldown = 10.f; 
    const float maxFenceLength = 500.f;
};