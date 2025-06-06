#pragma once

#include <list>
#include <memory>
#include <algorithm>
#include <unordered_map>

#include <raylib.h>

#include "entities/Entity.h"
#include "collider/CollisionSystem.h"
#include "score/ScoreKeeper.h"
#include "collider/Collider.h"
#include "entities/EntityType.h"

class Entity;
class GameData{
public:
    GameData(const std::string* playerName);
    void physicsUpdate();

    /// @brief Main logic loop for the game
    /// @param dt 
    /// @param lerpValue 
    /// @return A flag whether the game state should be reset
    bool gameUpdate(float dt, float lerpValue);
    std::unordered_map<DrawingLayer, std::vector<std::shared_ptr<Entity>>> prepareDraw();
    void registerEntity(std::shared_ptr<Entity> entity);
    // Right now this is used just for collecting statistics for shader effects
    // if convienient, it can be used to spawn bullets and handle logic for them
    void kill(std::shared_ptr<Entity> entity);
    float getTimeSinceKill();
    float getLastDamageTime();
    void handleCollisions();
    void deleteZombieEntities();
    bool checkPresent(EntityType type);
    void setPlayer(std::shared_ptr<Entity> player);
    Camera2D getMainCamera() const;
    void setMainCamera(Camera2D);
    Vector2 getMouseWorldPosition() const;
    static Rectangle getCameraVisionBoundaries(Camera2D camera);
    Vector2 lerp(Vector2 v1, Vector2 v2);
    float lerp(float v1, float v2);
    Vector2 playerPos() const;
    Vector2 playerVelocity() const;
    static void reset(GameData& gameData);
    void endGame();
    void saveScore();
    int getScore();
    Rectangle getMapBoundaries();
    std::vector<std::shared_ptr<Entity>> entitiesOfType(EntityType type);

    bool hasEnded=false;
    int scorePosition=-1;

    static constexpr float physicsDt = 1.0f/30.0f;
private:
    ScoreKeeper scoreKeeper;
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
    const std::string* playerName;
    Rectangle mapBoundaries{
        0, 0,
        1.3f * GetScreenWidth(),
        1.3f * GetScreenHeight()
    };

    // Statistics for shaders
    float timeSinceKill{-1.f};
};