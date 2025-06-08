#include "ElectricFence.h"
#include <raymath.h>

ElectricFence::ElectricFence(Collider collider)
: Entity(collider.p0, collider.p1, Vector2{0, 0}, 0, 0, DrawingLayer::BACKGROUND){
    posNow = collider.p0;
    this->collider = collider;
    loadShader("lightning");
}

void ElectricFence::gameUpdate(GameData& game, float dt){
    posNow = game.lerp(prevPos, pos);
    timer -= dt;
    if (timer < 0) {
        onDeath();
    }
}
void ElectricFence::physicsUpdate(GameData& game){
    prevPos = pos;
    pos = collider.p1;
}

void ElectricFence::draw() {
    float time = GetTime();
    SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT);
    float length = Vector2Distance(collider.p0, posNow);
    float dimensions[2] = {length, width};
    float angle = Vector2Angle({1, 0}, Vector2Subtract(posNow, collider.p0)) * RAD2DEG;
    SetShaderValue(shader, GetShaderLocation(shader, "resolution"), dimensions, SHADER_UNIFORM_VEC2);
    BeginShaderMode(shader);
    DrawRectanglePro(Rectangle{collider.p0.x, collider.p0.y, length, width}, {0, width/2}, angle, WHITE);
    EndShaderMode();
}

EntityType ElectricFence::type() {
    return PLAYER;
}