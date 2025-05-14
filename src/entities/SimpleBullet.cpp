#include "SimpleBullet.h"

#include <raymath.h>

#include "../GameData.h"

SimpleBullet::SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity, float rotation)
    : Entity(prevPos, pos, velocity,  BASE_RADIUS, rotation) {
    loadTexture("bullet.png", 0.2f);
}

void SimpleBullet::gameUpdate(GameData& game, float) {
    posNow = game.lerp(prevPos, pos);
}

void SimpleBullet::physicsUpdate(GameData& game) {
    prevPos = pos;
    pos += velocity * GameData::physicsDt;
}

void SimpleBullet::collide(std::shared_ptr<Entity> entity,GameData& gameData) {
    if(entity->type()==SIMPLE_ENEMY){
        onDeath();
    }
}

void SimpleBullet::draw() {
    drawTexture();
}

EntityType SimpleBullet::type() {
    return SIMPLE_BULLET;
}