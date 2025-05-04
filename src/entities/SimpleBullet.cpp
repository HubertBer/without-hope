#include "SimpleBullet.h"

#include <raymath.h>

#include "../GameData.h"

SimpleBullet::SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity, BASE_RADIUS) {
    collider = std::make_shared<Collider>(MakeCircleCollider(pos, hitboxRadius));
}

void SimpleBullet::start(GameData& game){
    game.registerEntityCollider({self, collider});
}

void SimpleBullet::gameUpdate(GameData& game, float) {
    posNow = game.lerp(prevPos, pos);
}

void SimpleBullet::physicsUpdate(GameData& game) {
    prevPos = pos;
    pos += velocity * GameData::physicsDt;
    collider->p0 = pos;
}

void SimpleBullet::collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData) {
    if(other.first.lock()->type()==SIMPLE_ENEMY){
        zombie=true;
    }
}

void SimpleBullet::draw() {
    DrawRectangle(static_cast<int>(posNow.x), static_cast<int>(posNow.y), 5, 20, YELLOW);
}

EntityType SimpleBullet::type() {
    return SIMPLE_BULLET;
}