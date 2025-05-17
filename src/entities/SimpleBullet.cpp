#include "SimpleBullet.h"

#include <raymath.h>

#include "../GameData.h"

SimpleBullet::SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity, float rotation)
    : Entity(prevPos, pos, velocity,  BASE_RADIUS, rotation, DrawingLayer::BLOOM) {
    loadTexture("bullet.png", 0.2f);
    collider = MakeCircleCollider(pos, hitboxRadius);
}

void SimpleBullet::gameUpdate(GameData& game, float) {
    posNow = game.lerp(prevPos, pos);
}

void SimpleBullet::physicsUpdate(GameData& game) {
    prevPos = pos;
    pos += velocity * GameData::physicsDt;
    collider.p0 = pos;

    Rectangle mapBoundaries = game.getMapBoundaries();
    if (pos.x < 0.0f || pos.x > mapBoundaries.width ||
        pos.y < 0.0f || pos.y > mapBoundaries.height) {
        onDeath();
    }
}

void SimpleBullet::collide(std::shared_ptr<Entity> other, GameData& gameData) {
    if(other->type()==SIMPLE_ENEMY){
        onDeath();
    }
}

void SimpleBullet::draw() {
    drawTexture();
}

EntityType SimpleBullet::type() {
    return SIMPLE_BULLET;
}