#include "CollectibleSpawner.h"
#include "../GameData.h"
#include "Collectible.h"
#include "../rand.h"

CollectibleSpawner::CollectibleSpawner() : Entity(Vector2{0,0}, Vector2{0,0}, Vector2{0,0}, 0) {}

void CollectibleSpawner::gameUpdate(GameData& game, float dt) {
    int score = game.getScore();
    if (score >= next_threshold) {
        auto mapBounds = game.getMapBoundaries();
        auto pos = Vector2{
            GetRandomFloat(mapBounds.x, mapBounds.x + mapBounds.width),
            GetRandomFloat(mapBounds.y, mapBounds.y + mapBounds.height),
        };
        game.registerEntity(std::make_shared<Collectible>(pos, game.isPlayerDamaged()));
        next_threshold += SCORE_THRESHOLD;
    }
}