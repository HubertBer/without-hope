#include "GameScene.h"
#include "../entities/Player.h"
#include "../entities/SimpleEnemy.h"
#include "../entities/SimpleSpawner.h"
#include "../particles/BasicParticleEffect.h"
#include "../rand.h"

void LoadGameScene(GameData& game){
    auto player = std::make_shared<Player>(
        Vector2{100.0, 100.0f},
        Vector2{100.0, 100.0f},
        Vector2{0.0f, 0.0f}
    );

    game.setPlayer(player);
    game.registerEntity(player);

    for(int i = 0; i < 10; ++i){
        Vector2 pos = {GetRandomFloat(300, 1000), GetRandomFloat(300, 1000)};
        game.registerEntity(std::make_shared<SimpleEnemy>(
        pos,
        pos,
        Vector2{0, 0}
        ));
    }

    game.registerEntity(std::make_shared<BasicParticleEffect>(Vector2{200.f, 200.f}));

    game.registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{0, 0, 100, 100},
        3,
        6
    ));

    game.registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{1000, 1000, 100, 100},
        3,
        6
    ));

    game.registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{1000, 0, 100, 100},
        3,
        6
    ));

    game.registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{0, 1000, 100, 100},
        3,
        6
    ));
}