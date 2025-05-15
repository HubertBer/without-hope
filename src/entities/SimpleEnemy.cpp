#include "SimpleEnemy.h"

#include <iostream>

#include <raymath.h>

#include "../GameData.h"

SimpleEnemy::SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity, BASE_RADIUS) {
    loadTexture("square.png", 0.5f);
    loadShader("bloom.fs");
    collider = MakeCircleCollider(pos, hitboxRadius);
}

void SimpleEnemy::gameUpdate(GameData& game, float) {
    posNow = game.lerp(prevPos, pos);
}

void SimpleEnemy::physicsUpdate(GameData& game) {
    prevPos = pos;
    velocity = Vector2Normalize(game.playerPos() - pos) * maxSpeed;
    pos += velocity * GameData::physicsDt;
    collider.p0 = pos;
}

void SimpleEnemy::collide(std::shared_ptr<Entity> other, GameData& gameData) {
    switch(other->type()){
        case SIMPLE_BULLET:
        case ELECTRIC_FENCE:
            onDeath();
    };
}

void SimpleEnemy::draw() {
    drawTexture();
}

EntityType SimpleEnemy::type() {
    return SIMPLE_ENEMY;
}
