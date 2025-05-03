#include "Minigun.h"
#include "../GameData.h"
#include "raymath.h"
#include "../entities/SimpleBullet.h"
#include <memory>
#include "../rand.h"

Minigun::Minigun(){}

void Minigun::gameUpdate(GameData& game, Player& player,  float dt){
    bulletCooldown -= dt;

    if(bulletCooldown <= 0.0f){
        Vector2 mousePos = game.getMouseWorldPosition();
        Vector2 bulletVel = Vector2Normalize(player.velocity);
        
        if(Vector2LengthSqr(bulletVel) < EPSILON){
            bulletVel = {1.0, 0.0f}; 
        }
        bulletVel = Vector2Normalize(bulletVel) * SimpleBullet::maxSpeed;
        float spread = spreadAngle * DEG2RAD;
        bulletVel = Vector2Rotate(bulletVel, GetRandomFloat(-spread, spread));

        game.registerEntity(std::make_shared<SimpleBullet>(
            player.pos,
            player.pos,
            bulletVel
        ));

        bulletCooldown += maxBulletCooldown;
    }
}

void Minigun::physicsUpdate(GameData& game, Player& player){
    
}