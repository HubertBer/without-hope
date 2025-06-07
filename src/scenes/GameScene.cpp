#include "GameScene.h"
#include "../entities/Player.h"
#include "../entities/SimpleEnemy.h"
#include "../entities/SimpleSpawner.h"
#include "../entities/GridBackground.h"
#include "../entities/TargetableCamera.h"
#include "../particles/BasicParticleEffect.h"
#include "../rand.h"
#include "../entities/Squadron.h"
#include "../entities/Trail.h"
#include "../entities/ShootingEnemy.h"
#include "../entities/Drone.h"
#include "../entities/OutsideMapSpawner.h"
#include "../entities/Collectible.h"
#include "../entities/CollectibleSpawner.h"

void LoadGameScene(GameData& game){
    Rectangle mapBoundaries = game.getMapBoundaries();
    Vector2 startingPos = {
        mapBoundaries.x + mapBoundaries.width / 2,
        mapBoundaries.y + mapBoundaries.height / 2
    };
    auto player = std::make_shared<Player>(
        startingPos,
        startingPos,
        Vector2{0.0f, 0.0f}
    );

    game.setPlayer(player);
    game.registerEntity(player);

    auto playerTrail = std::make_shared<Trail>(player, 4.f, 5.f, WHITE, false, true, DARKBLUE);
    game.registerEntity(playerTrail);

    auto targetableCamera = std::make_shared<TargetableCamera>(player);
    game.registerEntity(targetableCamera);

    auto gridBg = std::make_shared<GridBackground>();
    game.registerEntity(gridBg);
}