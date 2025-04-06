#include "Player.h"

#include <raymath.h>

#include "SimpleBullet.h"
#include "../GameData.h"

Player::Player(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity) {}

void Player::physicsUpdate(GameData& game) {
    prevPos = pos;
    pos += velocity * GameData::physicsDt;
}

void Player::gameUpdate(GameData& game, float dt) {
    velocity = {0, 0};
    if (IsKeyDown(KEY_D)) velocity.x += 1;
    if (IsKeyDown(KEY_A)) velocity.x -= 1;
    if (IsKeyDown(KEY_W)) velocity.y -= 1;
    if (IsKeyDown(KEY_S)) velocity.y += 1;
    if(Vector2LengthSqr(velocity) > EPSILON){
        velocity = Vector2Normalize(velocity);
        velocity *= maxSpeed;
    }

    if(IsKeyPressed(KEY_SPACE)){
        Vector2 bullet_vel = (pos - prevPos); //Later probably just based on rotation
        if(Vector2LengthSqr(bullet_vel) < EPSILON){
            bullet_vel = {1.0, 0.0f}; 
        }
        bullet_vel = Vector2Normalize(bullet_vel) * SimpleBullet::maxSpeed;

        game.registerEntity(std::make_shared<SimpleBullet>(
            pos,
            pos,
            bullet_vel
        ));
    }
}

void Player::draw(float lerpValue) {
    Vector2 playerPosNow = Vector2Lerp(prevPos, pos, lerpValue);        
    DrawCircle(static_cast<int>(playerPosNow.x), static_cast<int>(playerPosNow.y), 30, RED);
}
EntityType Player::type() {
    return PLAYER;
}