#pragma once

#include <raylib.h>
#include <memory>
#include "../collider/Collider.h"
#include "../collider/CollisionSystem.h"

class GameData;
class Collider;

enum EntityType{
    NONE,
    PLAYER,
    SIMPLE_ENEMY,
    SIMPLE_BULLET,
    SIMPLE_SPAWNER,
    TARGETABLE_CAMERA,
    GRID_BACKGROUND,
    ELECTRIC_FENCE,
};

enum DrawingLayer : uint16_t{
    BACKGROUND = 0,
    DEFAULT,
    FOREGROUND,
};

class Entity{
public:
    Entity(Vector2 prevPos, Vector2 pos, Vector2 velocity, float hitboxRadius, DrawingLayer drawLayer = DEFAULT)
        : prevPos(prevPos), pos(pos), velocity(velocity),hitboxRadius(hitboxRadius), drawLayer(drawLayer) {}
    /// @brief Function called every physics tick.
    /// @param  
    virtual void physicsUpdate(GameData&){}
    /// @brief Function called every frame. Put game logic here.
    /// @param game 
    /// @param dt 
    virtual void gameUpdate(GameData& game, float dt){}
    virtual void collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData){};
    virtual void draw(){}
    virtual EntityType type(){return NONE;}
    virtual std::pair<DrawingLayer, float> drawOrder(){return {drawLayer, pos.y};};
    virtual void start(GameData&){}

    Vector2 pos;
    Vector2 prevPos;
    Vector2 posNow;
    Vector2 velocity; 
    DrawingLayer drawLayer{DEFAULT};
    float hitboxRadius;
    bool zombie=false;

protected:
    std::weak_ptr<Entity> self;
    friend class GameData;
};
