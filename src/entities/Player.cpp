#include "Player.h"

#include <raymath.h>

#include "SimpleBullet.h"
#include "../GameData.h"
#include "../UI/Scaler.h"
#include "../weapons/Cannon.h"
#include "../weapons/Minigun.h"
#include "../weapons/ElectricFenceMaker.hpp"

Player::Player(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity, BASE_RADIUS, FOREGROUND) {
    weapons.push_back(std::make_shared<Cannon>());
    weapons.push_back(std::make_shared<Minigun>());
    weapons.push_back(std::make_shared<ElectricFenceMaker>());
    collider = std::make_shared<Collider>(MakeCircleCollider(pos, hitboxRadius));
}

void Player::start(GameData& game){
    game.registerEntityCollider({self, collider});
}

void Player::physicsUpdate(GameData& game) {
    prevPos = pos;
    pos += velocity * GameData::physicsDt;

    for(auto weapon : weapons){
        weapon->physicsUpdate(game, *this);
    }

    collider->p0 = pos;
}

void Player::gameUpdate(GameData& game, float dt) {
    posNow = game.lerp(prevPos, pos);

    velocity = {0, 0};
    if (IsKeyDown(KEY_D)) velocity.x += 1;
    if (IsKeyDown(KEY_A)) velocity.x -= 1;
    if (IsKeyDown(KEY_W)) velocity.y -= 1;
    if (IsKeyDown(KEY_S)) velocity.y += 1;
    if(Vector2LengthSqr(velocity) > EPSILON){
        velocity = Vector2Normalize(velocity);
        velocity *= maxSpeed;
    }

    for(auto weapon : weapons){
        weapon->gameUpdate(game, *this, dt);
    }
}

void Player::collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData) {
    if(other.first.lock()->type()==SIMPLE_ENEMY){
        velocity=Vector2{0.f,0.f};//insead say that game over or sth
        zombie=true;
    }
}

void Player::draw() {
    DrawCircle(static_cast<int>(posNow.x), static_cast<int>(posNow.y), 30, RED);
}

EntityType Player::type() {
    return PLAYER;
}