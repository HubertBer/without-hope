#include "SlowCircle.h"
#include <raymath.h>

SlowCircle::SlowCircle(Collider collider)
: Entity(collider.p0, collider.p0, Vector2{0, 0}, 0, 0, DrawingLayer::BACKGROUND){
    posNow = collider.p0;
    this->collider = collider;
}

void SlowCircle::gameUpdate(GameData& game, float dt){
    posNow = game.lerp(prevPos, pos);
}
void SlowCircle::physicsUpdate(GameData& game){
    prevPos = pos;
    radius += expansionSpeed * GameData::physicsDt;
    collider.radius = radius;
    collider.inside_radius = std::max(0.f,radius-outlineWidth);
    Rectangle mapBoundaries = game.getMapBoundaries();
    if (radius>2*mapBoundaries.width && radius > 2*mapBoundaries.height) {
        onDeath();
    }
}

void SlowCircle::draw() {
    DrawRing({collider.p0.x, collider.p0.y},collider.inside_radius, collider.radius, 0.f,360.f,0.f, Color{19, 163, 235, 255});
}

EntityType SlowCircle::type() {
    return PLAYER_SLOWER;
}