#include "Player.h"

#include <iostream>

#include <raymath.h>

#include "SimpleBullet.h"
#include "../GameData.h"
#include "../UI/Scaler.h"
#include "../weapons/Cannon.h"
#include "../weapons/Minigun.h"
#include "../weapons/ElectricFenceMaker.hpp"

#include <algorithm>
#include "../particles/BasicParticleEffect.h"
#include "../rand.h"

Player::Player(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity, BASE_RADIUS, 0, DrawingLayer::BLOOM) {
    loadTexture("player.png", 0.5f);
    weapons.push_back(std::make_shared<Cannon>());
    weapons.push_back(std::make_shared<Minigun>());
    weapons.push_back(std::make_shared<ElectricFenceMaker>());
    collider = MakeCircleCollider(pos, hitboxRadius);
}

void Player::physicsUpdate(GameData& game) {
    prevPos = pos;
    velocity += acceleration * GameData::physicsDt;
    if(Vector2Length(velocity) > maxSpeed){
        velocity = Vector2Normalize(velocity) * maxSpeed;
    }
    pos += velocity * GameData::physicsDt;

    for(auto weapon : weapons){
        weapon->physicsUpdate(game, *this);
    }

    collider.p0 = pos;

    Rectangle mapBoundaries = game.getMapBoundaries();
    pos = {
        std::clamp(pos.x, hitboxRadius, mapBoundaries.width - hitboxRadius),
        std::clamp(pos.y, hitboxRadius, mapBoundaries.height - hitboxRadius)
    };
}

void Player::gameUpdate(GameData& game, float dt) {
    posNow = game.lerp(prevPos, pos);

    Vector2 playerDir = game.getMouseWorldPosition() - posNow;
    rotation = Vector2Angle(Vector2{1, 0}, playerDir) * RAD2DEG;

    acceleration = Vector2{0.f, 0.f};
    if (IsKeyDown(KEY_D)) acceleration.x += 1;
    if (IsKeyDown(KEY_A)) acceleration.x -= 1;
    if (IsKeyDown(KEY_W)) acceleration.y -= 1;
    if (IsKeyDown(KEY_S)) acceleration.y += 1;
    if(Vector2LengthSqr(acceleration) > EPSILON){
        acceleration = Vector2Normalize(acceleration);
        acceleration *= maxAcceleration;
    }else{
        acceleration = Vector2Normalize(velocity) * maxSpeed * -1.f * friction;
    }

    for(auto weapon : weapons){
        weapon->gameUpdate(game, *this, dt);
    }
}

void Player::collide(std::shared_ptr<Entity> entity,GameData& gameData) {
    switch(entity->type()){
        case SIMPLE_ENEMY:
        case SQUADRON_SHIP:
            if (GetTime() - timeOfLastDamage > damageImmunity) {
                health -= 1;
                if (health == 0) {
                    velocity=Vector2{0.f,0.f}; // instead say that game over or sth
                    acceleration=Vector2{0.f,0.f};
                    zombie=true;
                } else {
                    textureTint = healthColorLerp();
                    timeOfLastDamage = GetTime();
                }
            }
    }
}

void Player::draw() {
    drawTexture();
}

Color Player::healthColorLerp()
{
    float t = (float)(health - 1)/maxHealth;
    static constexpr Color colorB{255, 255, 255, 255};
    static constexpr Color colorA{255, 0, 0, 255};

    Color result;
    result.r = colorA.r + (colorB.r - colorA.r) * t;
    result.g = colorA.g + (colorB.g - colorA.g) * t;
    result.b = colorA.b + (colorB.b - colorA.b) * t;
    result.a = colorA.a + (colorB.a - colorA.a) * t;

    return result;
}

EntityType Player::type() {
    return PLAYER;
}