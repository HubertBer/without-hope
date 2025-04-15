#pragma once

#include <list>
#include <memory>
#include <algorithm>

#include <raylib.h>

#include "entities/Entity.h"
#include "collider/CollisionSystem.h"

class GameData{
public:
    GameData();
    void physicsUpdate();
    void gameUpdate(float dt);
    void draw();
    void registerEntity(std::shared_ptr<Entity> entity);
    // Right now this is used just for collecting statistics for shader effects
    // if convienient, it can be used to spawn bullets and handle logic for them
    void kill();
    float getTimeSinceKill();
    void handleCollisions();
    void deleteZombieEntities();
    void spawnEnemies(float dt);
    Vector2 playerPos() const;

    static constexpr float physicsDt = 1.0f/60.0f;
private:
    CollisionSystem collisionSystem;
    std::list<std::shared_ptr<Entity>> entities;
    std::list<std::shared_ptr<Entity>> entitiesBuffer;
    std::shared_ptr<Entity> player;
    const float player_speed = 500.0f;
    const float enemy_spawn_cooldown = 3.0f;

    // Statistics for shaders
    float timeSinceKill{-1.f};
};