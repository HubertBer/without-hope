#include "SimpleEnemy.h"

#include <iostream>

#include <raymath.h>

#include "../GameData.h"

SimpleEnemy::SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity,BASE_RADIUS) {
    loadTexture("src/resources/sprites/square.png", 0.5f);
    loadShader("src/resources/shaders/bloom.fs");
}

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
    drawTexture();
}

EntityType SimpleEnemy::type() {
    return SIMPLE_ENEMY;
}
