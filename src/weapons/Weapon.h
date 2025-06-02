#pragma once

#include "../GameData.h"
#include "../entities/Player.h"
class Player;

enum class WeaponName {
    CANNON,
    MINIGUN,
    ELECTRIC_FENCE,
    LASER,
    DRONE_BAY,
    SLOW_CIRCLE,
};

class Weapon{
public:
    virtual void gameUpdate(GameData& game, Player& player, float dt) = 0;
    virtual void physicsUpdate(GameData& game, Player& player) = 0;
    virtual WeaponName getWeaponName() = 0;
};