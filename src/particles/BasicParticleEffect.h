#pragma once
#include "../entities/Entity.h"
#include <vector>

using MinMax = Vector2;

struct Particle{
    Vector2 pos;
    Vector2 prevPos;
    Vector2 posNow;
    Vector2 velocity;
    float radius;
    float lifetime;
    float baseLifetime;
    bool downscale;
};

class BasicParticleEffect : public Entity{
public:
    BasicParticleEffect(Vector2 pos, float rotation, float spread, 
        Vector2 radius, Vector2 speed, Vector2 lifetime, 
        Vector2 spawnCooldown, Vector2 burstCount, Color color);
    void physicsUpdate(GameData&) override;
    void gameUpdate(GameData& game, float dt) override;
    void collide(std::shared_ptr<Entity> entity,GameData& gameData) override;
    void draw() override;
    void stopSpawning();
    void resumeSpawning();
    EntityType type() override;

private:
    std::vector<Particle> particles;

    bool spawning = true;
    Vector2 direction{1.f, 0.f};
    float spread{15.f};
    MinMax radius{1.f, 10.f}; 
    MinMax speed{100.f, 1000.f};
    MinMax lifetime{0.3f, 1.2f};
    MinMax spawnCooldown{0.01f, 0.2f};
    float timer = 0.f;
    MinMax burstCount{1, 5};
    Color color = YELLOW;
};