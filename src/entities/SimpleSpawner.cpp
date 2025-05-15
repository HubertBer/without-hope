#include "SimpleSpawner.h"
#include "SimpleEnemy.h"
#include "../rand.h"

SimpleSpawner::SimpleSpawner(Rectangle boundingBox, float minDelay, float maxDelay)
: boundingBox(boundingBox), Entity({}, {}, {}, 0), minDelay(minDelay), maxDelay(maxDelay)
{
    timer = GetRandomFloat(minDelay, maxDelay);
}

void SimpleSpawner::gameUpdate(GameData& game, float dt){
    timer -= dt;
    if(timer < 0){
        Vector2 pos{
            GetRandomFloat(boundingBox.x, boundingBox.x + boundingBox.width),
            GetRandomFloat(boundingBox.y, boundingBox.y + boundingBox.height)
        };

        game.registerEntity(std::make_shared<SimpleEnemy>(
            pos,
            pos,
            Vector2{0,0}
        ));

        timer += GetRandomFloat(minDelay, maxDelay);
    }
}

EntityType SimpleSpawner::type() {
    return SIMPLE_SPAWNER; 
}