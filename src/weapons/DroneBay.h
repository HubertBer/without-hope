#pragma once


#include "Weapon.h"
#include "../entities/Drone.h"
#include <vector>
#include "../entities/Player.h"

class DroneBay : public Weapon{
public:
    DroneBay(){}
    void gameUpdate(GameData& game, Player& player, float dt) override;
    void physicsUpdate(GameData&, Player&) override;
    WeaponName getWeaponName() override { return WeaponName::DRONE_BAY; }
private:
    std::vector<std::weak_ptr<Drone>> drones;

    float timer = 0.f;

    static constexpr int MAX_DRONE_COUNT = 8;    
    static constexpr float COOLDOWN = 5.f; 
};