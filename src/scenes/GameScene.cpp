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

    auto playerTrail = std::make_shared<Trail>(player);
    game.registerEntity(playerTrail);

    auto targetableCamera = std::make_shared<TargetableCamera>(player);
    game.registerEntity(targetableCamera);

    auto gridBg = std::make_shared<GridBackground>();
    game.registerEntity(gridBg);

    game.registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{mapBoundaries.x - 150, mapBoundaries.y - 100, 100, mapBoundaries.height + 200},
        3,
        6
    ));

    game.registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{mapBoundaries.x + mapBoundaries.width + 50, mapBoundaries.y - 100, 100, mapBoundaries.height + 200},
        3,
        6
    ));

    game.registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{mapBoundaries.x - 100, mapBoundaries.y - 150, mapBoundaries.width + 200, 100},
        3,
        6
    ));

    game.registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{mapBoundaries.x - 100, mapBoundaries.y + mapBoundaries.height + 50, mapBoundaries.width + 200, 100},
        3,
        6
    ));

    game.registerEntity(std::make_shared<Squadron>(
        Vector2{-100, -100.f},
        180
    ));

    game.registerEntity(std::make_shared<ShootingEnemy>(
        Vector2{-1000.f, -1000.f }
    ));
    game.registerEntity(std::make_shared<ShootingEnemy>(
        Vector2{1000.f, 1000.f }
    ));
    game.registerEntity(std::make_shared<ShootingEnemy>(
        Vector2{-1000.f, 1000.f }
    ));
    game.registerEntity(std::make_shared<ShootingEnemy>(
        Vector2{1000.f, -1000.f }
    ));

    game.registerEntity(std::make_shared<Drone>(
        player->pos,
        GetRandomFloat(0, 360)
    ));

    game.registerEntity(std::make_shared<Drone>(
        player->pos,
        GetRandomFloat(0, 360)
    ));

    game.registerEntity(std::make_shared<Drone>(
        player->pos,
        GetRandomFloat(0, 360)
    ));
    game.registerEntity(std::make_shared<OutsideMapSpawner>(
        Vector2{4.f, 8.f}
    ));
    
    game.registerEntity(std::make_shared<OutsideMapSpawner>(
        Vector2{4.f, 8.f}
    ));
    
    game.registerEntity(std::make_shared<OutsideMapSpawner>(
        Vector2{4.f, 8.f}
    ));
}