#include "Laser.h"
#include "../GameData.h"
#include "raymath.h"
#include "../entities/LaserEntity.h"
#include <memory>

Laser::Laser(){}

void Laser::gameUpdate(GameData& game, Player& player,  float dt){
    bulletCooldown -= dt;

    if(bulletCooldown <= 0.0f){
        mousePos = game.getMouseWorldPosition();
        Vector2 dir = Vector2Normalize(mousePos - player.posNow);
        mousePos = player.posNow + dir * MIN_MOUSE_LENGTH;

        Collider laserCollider = MakeLineCollider(player.posNow, dir * LaserEntity::LASER_LENGTH);
        auto laser_spr = std::make_shared<LaserEntity>(laserCollider); 
        laser = laser_spr;
        game.registerEntity(laser_spr);

        bulletCooldown += maxBulletCooldown;
    }

    if(!laser.expired()) {
        laser.lock()->collider.p0 = player.posNow;
        laser.lock()->collider.p1 = mousePos;
    }
}

void Laser::physicsUpdate(GameData& game, Player& player){}