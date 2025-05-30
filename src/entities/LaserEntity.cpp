#include "LaserEntity.h"
#include <raymath.h>

LaserEntity::LaserEntity(Collider collider)
: Entity(collider.p0, collider.p1, Vector2{0, 0}, 0, 0, DrawingLayer::BLOOM){
    this->collider = collider;
    loadShader("lightning");
}

void LaserEntity::gameUpdate(GameData& game, float dt){
    lifetime -= dt;
    if(lifetime < 0) {
        onDeath();
    }
}

void LaserEntity::draw() {
    float time = GetTime();
    SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT);
    float length = LASER_LENGTH;
    float dimensions[2] = {length, width};
    float angle = Vector2Angle({1, 0}, (collider.p1 - collider.p0)) * RAD2DEG;
    SetShaderValue(shader, GetShaderLocation(shader, "resolution"), dimensions, SHADER_UNIFORM_VEC2);
    BeginShaderMode(shader);
    DrawRectanglePro(Rectangle{collider.p0.x, collider.p0.y, length, width}, {0, width/2}, angle, WHITE);
    EndShaderMode();
}

EntityType LaserEntity::type() {
    return PLAYER;
}