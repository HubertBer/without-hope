#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../GameData.h"
#include <vector>
#include "../weapons/Weapon.h"
#include "../particles/BasicParticleEffect.h"

class Weapon;

struct Player : public Entity{
public:
    Player(Vector2 prevPos, Vector2 pos, Vector2 velocity);
    void physicsUpdate(GameData& game) override;
    void gameUpdate(GameData& game, float dt) override;
    void collide(std::shared_ptr<Entity> other, GameData& gameData) override;
    void draw() override;
    void start(GameData&)override;
    Color healthColorLerp();
    EntityType type() override;

    static constexpr float BASE_RADIUS =30.f;
    static constexpr float maxSpeed = 500.0f;
    static constexpr float maxAcceleration = 1500.0f;
    static constexpr float friction = 0.5f;
    std::size_t health = 3;
    constexpr static std::size_t maxHealth = 3;
    float timeOfLastDamage = -5.f;
    constexpr static float damageImmunity = 1.f;
private:
    std::shared_ptr<BasicParticleEffect> movementParticles;
    Vector2 acceleration{0.f, 0.f};
    std::shared_ptr<Weapon> main_weapon;
    std::shared_ptr<Weapon> automatic_weapon;
    std::shared_ptr<Weapon> special_weapon;
};