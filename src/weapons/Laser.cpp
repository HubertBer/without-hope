#include "Laser.h"
#include "../GameData.h"
#include "raymath.h"
#include "../entities/LaserEntity.h"
#include <memory>

Laser::Laser(){}

void Laser::gameUpdate(GameData& game, Player& player,  float dt){
    bulletCooldown -= dt;

    if(bulletCooldown <= 0.0f){
        Vector2 mousePos = game.getMouseWorldPosition();
        

        Collider laserCollider = MakeLineCollider(player.pos, (mousePos-player.pos)*100);
        game.registerEntity(std::make_shared<LaserEntity>(laserCollider));

        bulletCooldown += maxBulletCooldown;
    }
}

void Laser::physicsUpdate(GameData& game, Player& player){}