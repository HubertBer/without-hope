#pragma once

#include <vector>
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
    void draw(float lerp_value);
    void registerEntity(std::shared_ptr<Entity> entity);
    void handleCollisions();
    Vector2 playerPos() const;

    static constexpr float physicsDt = 1.0f/60.0f;
private:
    CollisionSystem collisionSystem;
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> entitiesBuffer;
    std::shared_ptr<Entity> player;
    const float player_speed = 500.0f;
};