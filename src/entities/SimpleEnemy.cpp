#include "SimpleEnemy.h"

#include <raymath.h>

#include "../GameData.h"

SimpleEnemy::SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity) {}

void SimpleEnemy::gameUpdate(GameData& game, float dt) {}

void SimpleEnemy::physicsUpdate(GameData& game) {
    prevPos = pos;
    velocity = Vector2Normalize(game.playerPos() - pos) * maxSpeed;
    pos += velocity * GameData::physicsDt;
}

void SimpleEnemy::draw(float lerpValue) {
    Vector2 enemyPosNow = Vector2Lerp(prevPos, pos, lerpValue);        
    DrawRectangle(static_cast<int>(enemyPosNow.x), static_cast<int>(enemyPosNow.y), 20, 40, GREEN);
}

EntityType SimpleEnemy::type() {
    return SIMPLE_ENEMY;
}
