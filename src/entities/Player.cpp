#include "Player.h"

#include <raymath.h>

#include "SimpleBullet.h"
#include "../GameData.h"
#include "../UI/Scaler.h"

Player::Player(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity,BASE_RADIUS) {}

void Player::physicsUpdate(GameData& game) {
    prevPos = pos;
    pos += velocity * GameData::physicsDt;
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

    bulletCooldown-=dt;
    if(bulletCooldown<=0.0f){
        Vector2 mousePos = getVirtualPosition(GetMousePosition());
        Vector2 bullet_vel = (mousePos -  pos);
        
        if(Vector2LengthSqr(bullet_vel) < EPSILON){
            bullet_vel = {1.0, 0.0f}; 
        }
        bullet_vel = Vector2Normalize(bullet_vel) * SimpleBullet::maxSpeed;

        game.registerEntity(std::make_shared<SimpleBullet>(
            pos,
            pos,
            bullet_vel
        ));
        bulletCooldown += maxBulletCooldown;
    }
}

void Player::collide(std::shared_ptr<Entity> entity,GameData& gameData ) {
    if(entity->type()==SIMPLE_ENEMY){
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