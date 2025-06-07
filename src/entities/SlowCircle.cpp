#include "SlowCircle.h"
#include <raymath.h>

SlowCircle::SlowCircle(Collider collider)
: Entity(collider.p0, collider.p0, Vector2{0, 0}, 0, 0, DrawingLayer::BACKGROUND){
    posNow = collider.p0;
    this->collider = collider;
    loadShader("slow_circle");
}

void SlowCircle::gameUpdate(GameData& game, float dt){
    posNow = game.lerp(prevPos, pos);
    radiusNow = game.lerp(prevRadius, radius);
}

void SlowCircle::physicsUpdate(GameData& game){
    prevPos = pos;
    prevRadius = radius;
    radius += expansionSpeed * GameData::physicsDt;
    collider.radius = radius;
    collider.inside_radius = std::max(0.f,radius-outlineWidth);
    Rectangle mapBoundaries = game.getMapBoundaries();
    if (radius>2*mapBoundaries.width && radius > 2*mapBoundaries.height) {
        onDeath();
    }
}

void SlowCircle::draw() {
    float ringWidth = outlineWidth/(2 * radiusNow);
    SetShaderValue(shader, GetShaderLocation(shader, "ringWidth"), &ringWidth, SHADER_UNIFORM_FLOAT);
    float time = GetTime();
    SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT);

    BeginShaderMode(shader);
    DrawRectangle(collider.p0.x - radiusNow, collider.p0.y - radiusNow,
                   2 * radiusNow, 2 * radiusNow, ORANGE);
    EndShaderMode();
}

EntityType SlowCircle::type() {
    return PLAYER_SLOWER;
}