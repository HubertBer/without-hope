#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../collider/Collider.h"

class ShootingEnemy : public Entity{
public:
    ShootingEnemy(Vector2 pos);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> other, GameData& gameData) override;
    void draw() override;
    EntityType type() override;
    int getScore() override{return score;}
    void onDeath() override;

private:
    float reload_timer;
    float burst_timer;
    float bullets_to_fire; 
    Vector2 acceleration{0, 0};

    static constexpr float BASE_RADIUS = 10.f;
    static constexpr float maxSpeed = 150.f;
    static constexpr int score = 20;

    static constexpr float TARGET_DISTANCE = 200.f;
    static constexpr float REALOAD_TIME = 2.f;
    static constexpr float BURST_SIZE = 5;
    static constexpr float BURST_DELAY = 0.05f;
    static constexpr float MAX_ACCELERATION = 400.0f;
    static constexpr Color BULLET_COLOR{RED};
    static constexpr float DEFAULT_VELOCITY_MODIFIER = 1.0f;
    float velocityModifier=1.0f;
    float velocityModifierDuration=0.0f;
};