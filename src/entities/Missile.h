#pragma once

#include "Entity.h"
#include "raylib.h"
#include <memory>
#include "../particles/BasicParticleEffect.h"

class Missile : public Entity {
public:
    Missile(Vector2 pos, std::weak_ptr<Entity> target);
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> other, GameData& gameData) override;
    void draw() override;
    void start(GameData&) override;
    void onDeathLocal();
    EntityType type() override;

private:
    std::shared_ptr<BasicParticleEffect> movementParticles;
    std::weak_ptr<Entity> target;
    Vector2 acceleration{0.f, 0.f};

    static constexpr float BASE_RADIUS = 8.f;
    static constexpr float MAX_SPEED = 1000.f;
    static constexpr float START_SPEED_FRAC = 0.7f;
    static constexpr float MAX_ACCELERATION = 2500.f;
    static constexpr Color color{YELLOW};
    static constexpr float RAND_ANGLE = 50.f;
};