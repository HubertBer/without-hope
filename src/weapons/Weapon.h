#pragma once

#include "../GameData.h"
#include "../entities/Player.h"
class Player;

class Weapon{
public:
    virtual void gameUpdate(GameData& game, Player& player, float dt) = 0;
    virtual void physicsUpdate(GameData& game, Player& player) = 0;
};