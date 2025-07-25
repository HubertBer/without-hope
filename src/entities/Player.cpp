#include "Player.h"

#include <iostream>
#include <algorithm>
#include <memory>
#include <raymath.h>

#include "SimpleBullet.h"
#include "../GameData.h"
#include "../UI/Scaler.h"
#include "../weapons/Cannon.h"
#include "../weapons/Minigun.h"
#include "../weapons/ElectricFenceMaker.hpp"
#include "../weapons/DroneBay.h"
#include "../weapons/Laser.h"
#include "../weapons/SlowCircleMaker.hpp"

#include "../particles/BasicParticleEffect.h"
#include "../rand.h"
#include "Collectible.h"

Player::Player(Vector2 prevPos, Vector2 pos, Vector2 velocity)
    : Entity(prevPos, pos, velocity, BASE_RADIUS, 0, DrawingLayer::BLOOM) {
    loadTexture("player.png", 0.5f);
    main_weapon = std::make_shared<Cannon>();
    // automatic_weapon = std::make_shared<Minigun>();
    // special_weapon = std::make_shared<ElectricFenceMaker>();
    collider = MakeCircleCollider(pos, hitboxRadius);
}

void Player::physicsUpdate(GameData& game) {
    prevPos = pos;
    velocity += acceleration * velocityModifier*GameData::physicsDt;
    if(Vector2Length(velocity) > maxSpeed*velocityModifier){
        velocity = Vector2Normalize(velocity) * maxSpeed*velocityModifier;
    }
    if(Vector2Length(velocity) < 10) {
        velocity = Vector2Zero();
    }
    pos += velocity * GameData::physicsDt;

    if (main_weapon) {
        main_weapon->physicsUpdate(game, *this);
    }
    if (automatic_weapon) {
        automatic_weapon->physicsUpdate(game, *this);
    }
    if (special_weapon) {
        special_weapon->physicsUpdate(game, *this);
    }

    collider.p0 = pos;

    Rectangle mapBoundaries = game.getMapBoundaries();
    pos = {
        std::clamp(pos.x, hitboxRadius, mapBoundaries.width - hitboxRadius),
        std::clamp(pos.y, hitboxRadius, mapBoundaries.height - hitboxRadius)
    };

    movementParticles->pos = pos;
    movementParticles->prevPos = prevPos;
}

void Player::start(GameData& game){
    movementParticles = std::make_shared<BasicParticleEffect>(
        pos,
        rotation,
        30.f,
        Vector2{0.6f, 2.8f},
        Vector2{0.5f * maxSpeed, 1.f * maxSpeed},
        Vector2{.08f, .2f},
        Vector2{.01f, .03f},
        Vector2{4, 8},
        WHITE
    );
    game.setShowTutorial(true,"! PRESS SHIFT !");
    game.registerEntity(movementParticles);
}

void Player::gameUpdate(GameData& game, float dt) {
    posNow = game.lerp(prevPos, pos);

    Vector2 playerDir = game.getMouseWorldPosition() - posNow;
    rotation = Vector2Angle(Vector2{1, 0}, playerDir) * RAD2DEG;
    sprint_timer -= dt;
    velocityModifierDuration -= dt;
    if(velocityModifierDuration<0.f){
        velocityModifier=DEFAULT_VELOCITY_MODIFIER;
    }

    if((IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT))&&sprint_timer<0.0f){
        sprint_timer=sprint_cooldown;
        velocityModifierDuration=0.3f;
        velocityModifier=2.5f;
    }

    acceleration = Vector2{0.f, 0.f};
    if (IsKeyDown(KEY_D)) acceleration.x += 1;
    if (IsKeyDown(KEY_A)) acceleration.x -= 1;
    if (IsKeyDown(KEY_W)) acceleration.y -= 1;
    if (IsKeyDown(KEY_S)) acceleration.y += 1;
    if(Vector2LengthSqr(acceleration) > EPSILON){
        acceleration = Vector2Normalize(acceleration);
        acceleration *= maxAcceleration*velocityModifier;
        movementParticles->rotation = Vector2Angle(Vector2{1, 0}, acceleration * -1.f) * RAD2DEG;
        movementParticles->resumeSpawning();
    }else{
        acceleration = Vector2Normalize(velocity) * maxSpeed*velocityModifier* -1.f * friction;
        movementParticles->stopSpawning();
    }

    if (main_weapon) {
        main_weapon->gameUpdate(game, *this, dt);
    }
    if (automatic_weapon) {
        automatic_weapon->gameUpdate(game, *this, dt);
    }
    if (special_weapon) {
        special_weapon->gameUpdate(game, *this, dt);
    }
}

void Player::collide(std::shared_ptr<Entity> entity,GameData& gameData) {
    if(entity->type() == EntityType::ENEMY){
        if (GetTime() - timeOfLastDamage > damageImmunity) {
            health -= 1;
            if (health == 0) {
                velocity=Vector2{0.f,0.f}; // instead say that game over or sth
                acceleration=Vector2{0.f,0.f};
                zombie=true;
                movementParticles->zombie = true;
            } else {
                textureTint = healthColorLerp();
                timeOfLastDamage = GetTime();
            }
        }
    }

    if (entity->type() == EntityType::COLLECTIBLE) {
        auto collectible = dynamic_cast<Collectible*>(entity.get());
        switch (collectible->weapon) {
            case WeaponType::AUTOMATIC :
                if (!automatic_weapon) {
                    automatic_weapon = std::make_shared<Minigun>();
                    std::cout << "SWITCHED TO MINIGUN" << std::endl;
                    break;
                }
            
                if (automatic_weapon->getWeaponName() == WeaponName::MINIGUN) {
                    automatic_weapon = std::make_shared<DroneBay>();
                    std::cout << "SWITCHED TO DRONE BAY" << std::endl;
                } else {
                    automatic_weapon = std::make_shared<Minigun>();
                    std::cout << "SWITCHED TO MINIGUN" << std::endl;
                }
                break;
            case WeaponType::MAIN :
                if (!main_weapon) {
                    main_weapon = std::make_shared<Cannon>();
                    std::cout << "SWITCHED TO CANNON" << std::endl;
                    break;
                }

                if (main_weapon->getWeaponName() == WeaponName::CANNON) {
                    main_weapon = std::make_shared<Laser>();
                    std::cout << "SWITCHED TO LASER" << std::endl;
                } else {
                    main_weapon = std::make_shared<Cannon>();
                    std::cout << "SWITCHED TO CANNON" << std::endl;
                }
                break;
            case WeaponType::SPECIAL :
                gameData.setShowTutorial(true,"! PRESS SPACE !");
                if (!special_weapon) {
                    special_weapon = std::make_shared<ElectricFenceMaker>();
                    std::cout << "SWITCHED TO ELECTRIC FENCE" << std::endl;
                    break;
                }

                if (special_weapon->getWeaponName() == WeaponName::ELECTRIC_FENCE) {
                    special_weapon = std::make_shared<SlowCircleMaker>();
                    std::cout << "SWITCHED TO SLOW CIRCLE" << std::endl;
                } else {
                    special_weapon = std::make_shared<ElectricFenceMaker>();
                    std::cout << "SWITCHED TO ELECTRIC FENCE" << std::endl;
                }
                break;
            case WeaponType::HEALTH :
                if(health < 3) {
                    health += 1;
                    textureTint = healthColorLerp();
                }
                break;
        };
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