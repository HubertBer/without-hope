#include "SimpleEnemy.h"

#include <iostream>

#include <raymath.h>

#include "../GameData.h"

SimpleEnemy::SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity, BASE_RADIUS) {
    loadTexture("src/resources/sprites/square.png", 0.5f);
    loadShader("src/resources/shaders/bloom.fs");
    collider = std::make_shared<Collider>(MakeCircleCollider(pos, hitboxRadius));
}

void SimpleEnemy::gameUpdate(GameData& game, float) {
    posNow = game.lerp(prevPos, pos);
}

void SimpleEnemy::physicsUpdate(GameData& game) {
    prevPos = pos;
    velocity = Vector2Normalize(game.playerPos() - pos) * maxSpeed;
    pos += velocity * GameData::physicsDt;
    collider->p0 = pos;
}

void SimpleEnemy::collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData) {
    if(other.first.lock()->type()==SIMPLE_BULLET){
        zombie=true;
        gameData.kill();
    }
    if(other.first.lock()->type()==ELECTRIC_FENCE){
        zombie=true;
        gameData.kill();
    }
}

void SimpleEnemy::start(GameData& game){
    game.registerEntityCollider({self, collider});
}

void SimpleEnemy::draw() {
    drawTexture();
}

EntityType SimpleEnemy::type() {
    return SIMPLE_ENEMY;
}
