#include "SimpleEnemy.h"

#include <raymath.h>

#include "../GameData.h"

SimpleEnemy::SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity,BASE_RADIUS) {}

void SimpleEnemy::gameUpdate(GameData& game, float) {
    posNow = game.lerp(prevPos, pos);
}

void SimpleEnemy::physicsUpdate(GameData& game) {
    prevPos = pos;
    velocity = Vector2Normalize(game.playerPos() - pos) * maxSpeed;
    pos += velocity * GameData::physicsDt;
}

void SimpleEnemy::collide(std::shared_ptr<Entity> entity,GameData& gameData) {
    if(entity->type()==SIMPLE_BULLET){
        zombie=true;
        gameData.kill();
    }
}

void SimpleEnemy::draw() {
    DrawRectangle(static_cast<int>(posNow.x), static_cast<int>(posNow.y), 20, 40, GREEN);
}

EntityType SimpleEnemy::type() {
    return SIMPLE_ENEMY;
}
