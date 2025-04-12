#include "SimpleBullet.h"

#include <raymath.h>

#include "../GameData.h"

SimpleBullet::SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity,BASE_RADIUS) {}

void SimpleBullet::gameUpdate(GameData& game, float dt) {}

void SimpleBullet::physicsUpdate(GameData& game) {
    prevPos = pos;
    pos += velocity * GameData::physicsDt;
}

void SimpleBullet::collide(std::shared_ptr<Entity> entity,GameData& gameData) {
    if(entity->type()==SIMPLE_ENEMY){
        zombie=true;
    }
}

void SimpleBullet::draw(float lerpValue) {
    Vector2 bulletPosNow = Vector2Lerp(prevPos, pos, lerpValue);        
    DrawRectangle(static_cast<int>(bulletPosNow.x), static_cast<int>(bulletPosNow.y), 5, 20, YELLOW);
}

EntityType SimpleBullet::type() {
    return SIMPLE_BULLET;
}