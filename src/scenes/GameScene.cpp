#include "GameScene.h"
#include "../entities/Player.h"
#include "../entities/SimpleEnemy.h"

void LoadGameScene(GameData& game){
    auto player = std::make_shared<Player>(
        Vector2{100.0, 100.0f},
        Vector2{100.0, 100.0f},
        Vector2{0.0f, 0.0f}
    );

    game.setPlayer(player);
    game.registerEntity(player);

    for(int i = 0; i < 10; ++i){
        Vector2 pos = {(float)GetRandomValue(300, 1000), (float)GetRandomValue(300, 1000)};
        
        game.registerEntity(std::make_shared<SimpleEnemy>(
            pos,
            pos,
            Vector2{0, 0}
        ));
    }
}