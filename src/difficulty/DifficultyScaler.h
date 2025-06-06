#pragma once

#include <memory>
#include <functional>
#include <vector>

#include <raylib.h>

#include "../entities/SimpleEnemy.h"
#include "../entities/ShootingEnemy.h"
#include "../entities/Drone.h"
#include "../entities/Squadron.h"
#include "../entities/SquadronShip.h"

#include "../GameData.h"

/*
    The new entity creation should resemble the Poisson process based on the time differance and the difficulty rate and score, hence 
    making it stateless.
*/

class DifficultyScaler {
public:
    static void increaseDifficulty(GameData& game, float dt, float difficultyRate = 1.f); // spawn entities

private:
    struct EntityConfig {
        /*  
            // *roughly* the expected time in seconds between spawns with difficultyRate = 1.f.
            scales with score, so 'decreases' fast at the beginning.
        */
        float spawnRate; 
        std::function<void(GameData&, Vector2 vec)> entityFactory;
    };

    static std::vector<EntityConfig> entityConfigs;
};