#include "ElectricFence.h"

ElectricFence::ElectricFence(std::shared_ptr<Collider> collider)
:   Entity(collider->p0, collider->p1, Vector2{0, 0}, 0, 0, BACKGROUND), 
    collider(collider){}

void ElectricFence::gameUpdate(GameData& game, float dt){
    posNow = game.lerp(prevPos, pos);
}
void ElectricFence::physicsUpdate(GameData& game){
    prevPos = pos;
    pos = collider->p1;
}
void ElectricFence::collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData){}

void ElectricFence::draw() {
    DrawLineEx(collider->p0, posNow, width, color);
}

void ElectricFence::start(GameData&) {}

EntityType ElectricFence::type() {
    return ELECTRIC_FENCE;
}