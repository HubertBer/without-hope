#pragma once

#include "Missile.h"
#include <memory>
#include "Entity.h"
#include "raymath.h"
#include "../rand.h"
#include "../GameData.h"

Missile::Missile(Vector2 pos, std::weak_ptr<Entity> target) 
    :Entity(pos, pos, Vector2{0,0}, BASE_RADIUS, 0, DrawingLayer::BLOOM),
    target(target)
{    
    loadTexture("bullet.png", 0.25f);
    collider = MakeCircleCollider(pos, hitboxRadius);
    textureTint = color;

    Vector2 dir = Vector2Normalize(target.lock()->pos - pos);
    float angle = GetRandomFloat(-RAND_ANGLE, RAND_ANGLE) * DEG2RAD;
    dir = Vector2Rotate(dir, angle);    
    rotation = angle * RAD2DEG;
    velocity = dir * MAX_SPEED * START_SPEED_FRAC;
}

void Missile::start(GameData& game) {
    movementParticles = std::make_shared<BasicParticleEffect>(
        pos,
        rotation + 180,
        15,
        Vector2{1,5},
        Vector2{500, 1000},
        Vector2{.02, .05},
        Vector2{0.02, 0.1},
        Vector2{3, 10},
        RED
    );
    game.registerEntity(movementParticles);
}

void Missile::physicsUpdate(GameData& game) {
    prevPos = pos;
    if(target.expired()) {
        onDeathLocal();
        return;
    }
    acceleration = Vector2Normalize(target.lock()->pos - pos) * MAX_ACCELERATION;
    velocity += acceleration * GameData::physicsDt;
    if (Vector2Length(velocity) > MAX_SPEED) {
        velocity = Vector2Normalize(velocity) * MAX_SPEED;
    }
    rotation = Vector2Angle(Vector2{1, 0}, velocity) * RAD2DEG;
    
    pos += velocity * GameData::physicsDt;
    collider.p0 = pos;

    Rectangle mapBoundaries = game.getMapBoundaries();
    if (pos.x < 0.0f || pos.x > mapBoundaries.width ||
        pos.y < 0.0f || pos.y > mapBoundaries.height) {
        onDeathLocal();
        return;
    }

    movementParticles->pos = pos;
    movementParticles->prevPos = prevPos;
    movementParticles->rotation = Vector2Angle(Vector2{1, 0}, velocity * -1.f) * RAD2DEG;
}

void Missile::collide(std::shared_ptr<Entity> other, GameData& gameData) {
    if(other->type() == ENEMY) {
        onDeathLocal();
    }
}

void Missile::onDeathLocal() {
    movementParticles->onDeath();
    onDeath();
}

void Missile::draw() {
    drawTexture();
}

EntityType Missile::type() {
    return PLAYER;
}