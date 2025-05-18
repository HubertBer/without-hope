#include "GameScene.h"
#include "../entities/Player.h"
#include "../entities/SimpleEnemy.h"
#include "../entities/SimpleSpawner.h"
#include "../entities/GridBackground.h"
#include "../entities/TargetableCamera.h"
#include "../rand.h"
#include "../entities/Squadron.h"

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

    auto targetableCamera = std::make_shared<TargetableCamera>(player);
    game.registerEntity(targetableCamera);

    auto gridBg = std::make_shared<GridBackground>();
    game.registerEntity(gridBg);

    for(int i = 0; i < 10; ++i){
        Vector2 pos = {GetRandomFloat(0.0f, mapBoundaries.width), GetRandomFloat(0.0f, mapBoundaries.height)};
        game.registerEntity(std::make_shared<SimpleEnemy>(
        pos,
        pos,
        Vector2{0, 0}
        ));
    }

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
}