#include "ElectricFence.h"

ElectricFence::ElectricFence(Collider collider)
: Entity(collider.p0, collider.p1, Vector2{0, 0}, 0, 0, DrawingLayer::BACKGROUND){
        posNow = collider.p0;
        this->collider = collider;
    }

void ElectricFence::gameUpdate(GameData& game, float dt){
    posNow = game.lerp(prevPos, pos);
}
void ElectricFence::physicsUpdate(GameData& game){
    prevPos = pos;
    pos = collider.p1;
}

void ElectricFence::draw() {
    DrawLineEx(collider.p0, posNow, width, color);
}

EntityType ElectricFence::type() {
    return ELECTRIC_FENCE;
}