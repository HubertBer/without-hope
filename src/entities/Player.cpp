#include "Player.h"

#include <raymath.h>

#include "SimpleBullet.h"
#include "../GameData.h"
#include "../UI/Scaler.h"
#include "../weapons/Cannon.h"
#include "../weapons/Minigun.h"
#include "../weapons/ElectricFenceMaker.hpp"

Player::Player(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity, BASE_RADIUS, 0, FOREGROUND) {
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

void Player::collide(std::shared_ptr<Entity> other, GameData& gameData) {
    if(other->type() == SIMPLE_ENEMY){
        velocity=Vector2{0.f,0.f};//insead say that game over or sth
        acceleration=Vector2{0.f,0.f};//insead say that game over or sth
        zombie=true;
    }
}

void Player::draw() {
    drawTexture();
}

EntityType Player::type() {
    return PLAYER;
}