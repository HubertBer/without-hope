#include "SimpleSpawner.h"
#include "SimpleEnemy.h"

SimpleSpawner::SimpleSpawner(Rectangle boundingBox, float minDelay, float maxDelay)
: boundingBox(boundingBox), Entity({}, {}, {}, 0), minDelay(minDelay), maxDelay(maxDelay)
{
    timer = GetRandomValue(minDelay * 1024, maxDelay * 1024) / 1024.0f;
}

void SimpleSpawner::gameUpdate(GameData& game, float dt){
    timer -= dt;
    if(timer < 0){
        Vector2 pos{
            boundingBox.x + GetRandomValue(0, boundingBox.width * 1024) / 1024.0f,
            boundingBox.y + GetRandomValue(0, boundingBox.height * 1024) / 1024.0f,
        };

        game.registerEntity(std::make_shared<SimpleEnemy>(
            pos,
            pos,
            Vector2{0,0}
        ));

        timer += GetRandomValue(minDelay * 1024, maxDelay * 1024) / 1024.0f;
    }
}

void SimpleSpawner::physicsUpdate(GameData& game){}
void SimpleSpawner::collide(std::shared_ptr<Entity> other, GameData& game){}
void SimpleSpawner::draw(){}

EntityType SimpleSpawner::type() {
    return SIMPLE_SPAWNER; 
}