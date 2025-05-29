#include "DroneBay.h"
#include <algorithm>
#include "../rand.h"

void DroneBay::gameUpdate(GameData& game, Player& player, float dt) {
    timer -= dt;
    
    std::erase_if(drones, [](auto dr){return dr.expired();});
    
    if (timer > 0 || drones.size() >= MAX_DRONE_COUNT) {
        return;
    }

    auto drone = std::make_shared<Drone>(player.pos, GetRandomFloat(0, 360));
    game.registerEntity(drone);
    drones.push_back(drone);
    timer = COOLDOWN;
}

void DroneBay::physicsUpdate(GameData&, Player&) {}