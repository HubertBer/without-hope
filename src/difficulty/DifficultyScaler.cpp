#include "DifficultyScaler.h"

#include <cmath>
#include <iostream>
#include <chrono>

#include "../rand.h"

void DifficultyScaler::increaseDifficulty(GameData& game, float dt, float difficultyRate) {
    float lambda = difficultyRate * (1.f + std::log(game.getScore() + 1.f)) * dt / 3.f; // *magic* constant to account for the early rapid growth.

    for (const auto& config : entityConfigs) {
        if (game.getScore() < 350 && config.type == EnemyType::SQUADRON) {
            // Dont spawn squadron it's to OP
            continue;
        }

        if (GetRandomFloat(0.f, 1.f) < lambda / config.spawnRate) {
            Rectangle mapBoundaries = game.getMapBoundaries();
            float x0 = mapBoundaries.x, 
                  y0 = mapBoundaries.y,
                  x1 = mapBoundaries.x + mapBoundaries.width,
                  y1 = mapBoundaries.y + mapBoundaries.height;

            float x = GetRandomFloat(x0, x1);
            float y = GetRandomFloat(y0, y1);

            bool align_X_axis = GetRandomFloat(0.f, 1.f) < 0.5f;
            bool align_clockwise = GetRandomFloat(0.f, 1.f) < 0.5f;
            if (align_X_axis) {
                x = align_clockwise ? x0 : x1;
            }
            else {
                y = align_clockwise ? y0 : y1;
            }

            config.entityFactory(game, Vector2{x, y});
        }
    }
}

std::vector<DifficultyScaler::EntityConfig> DifficultyScaler::entityConfigs = {
    {EnemyType::SIMPLE, 5.f, [](GameData& game, Vector2 pos) { game.registerEntity(std::make_shared<SimpleEnemy>(pos, pos, Vector2{0, 0})); }},
    {EnemyType::SHOOTING, 30.f, [](GameData& game, Vector2 pos) { game.registerEntity(std::make_shared<ShootingEnemy>(pos)); }},
    {EnemyType::SQUADRON, 60.f, [](GameData& game, Vector2 pos) { game.registerEntity(std::make_shared<Squadron>(pos, 180.f)); }},
};