#include "Cannon.h"
#include "../GameData.h"
#include "raymath.h"
#include "../entities/SimpleBullet.h"
#include <memory>

Cannon::Cannon(){}

void Cannon::gameUpdate(GameData& game, Player& player,  float dt){
    bulletCooldown -= dt;

    if(bulletCooldown <= 0.0f){
        Vector2 mousePos = game.getMouseWorldPosition();
        Vector2 bullet_vel = (mousePos -  player.pos);
        
        if(Vector2LengthSqr(bullet_vel) < EPSILON){
            bullet_vel = {1.0, 0.0f}; 
        }
        bullet_vel = Vector2Normalize(bullet_vel) * SimpleBullet::maxSpeed;

        game.registerEntity(std::make_shared<SimpleBullet>(
            player.pos,
            player.pos,
            bullet_vel
        ));

        bulletCooldown += maxBulletCooldown;
    }
}

void Cannon::physicsUpdate(GameData& game, Player& player){}