#pragma once

#include <list>
#include <memory>
#include <algorithm>

#include <raylib.h>

#include "entities/Entity.h"
#include "collider/CollisionSystem.h"
#include "collider/Collider.h"
#include "entities/EntityType.h"

class CollisionSystem;
class Entity;
class Collider;

class GameData{
public:
    GameData();
    void physicsUpdate();
    void gameUpdate(float dt, float lerpValue);
    void draw();
    void registerEntity(std::shared_ptr<Entity> entity);
    void registerEntityCollider(std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> ec);
    // Right now this is used just for collecting statistics for shader effects
    // if convienient, it can be used to spawn bullets and handle logic for them
    void kill();
    float getTimeSinceKill();
    void handleCollisions();
    void deleteZombieEntities();
    bool checkPresent(EntityType type);
    void setPlayer(std::shared_ptr<Entity> player);
    Camera2D getMainCamera() const;
    void setMainCamera(Camera2D);
    Vector2 getMouseWorldPosition() const;
    Rectangle getCameraVisionBoundaries() const;
    Vector2 lerp(Vector2 v1, Vector2 v2);
    Vector2 playerPos() const;

    static constexpr float physicsDt = 1.0f/30.0f;
private:
    void resetGame();
    std::shared_ptr<CollisionSystem> collisionSystem;
    std::list<std::shared_ptr<Entity>> entities;
    std::list<std::shared_ptr<Entity>> entitiesBuffer;
    std::shared_ptr<Entity> player;
    const float player_speed = 500.0f;
    float lerpValue = 0.0f;
    Camera2D mainCamera{
        Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f},
        Vector2{0, 0},
        0,
        1.0f
    };

    // Statistics for shaders
    float timeSinceKill{-1.f};
};