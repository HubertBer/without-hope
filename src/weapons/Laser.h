#pragma once

#include "Weapon.h"
#include "../GameData.h"
#include "../entities/Entity.h"
#include "../entities/Player.h"
#include "../entities/LaserEntity.h"
#include <memory>

class Laser : public Weapon{
public:
    Laser();
    void gameUpdate(GameData& game, Player& player, float dt) override;
    void physicsUpdate(GameData& game, Player& player) override;

private:
    Vector2 mousePos;
    float bulletCooldown = 1.0f;
    float maxBulletCooldown = 2.0f;
    std::weak_ptr<LaserEntity> laser;
    
    static constexpr float MIN_MOUSE_LENGTH = 500.f;
};