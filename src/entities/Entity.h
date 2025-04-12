#pragma once

#include <raylib.h>
#include <memory>

class GameData;

enum EntityType{
    NONE,
    PLAYER,
    SIMPLE_ENEMY,
    SIMPLE_BULLET,
};

class Entity{
public:
    Entity(Vector2 prevPos, Vector2 pos, Vector2 velocity,float hitboxRadius)
        : prevPos(prevPos), pos(pos), velocity(velocity),hitboxRadius(hitboxRadius) {}
    /// @brief Function called every physics tick.
    /// @param  
    virtual void physicsUpdate(GameData&){}
    /// @brief Function called every frame. Put game logic here.
    /// @param game 
    /// @param dt 
    virtual void gameUpdate(GameData& game, float dt){}
    virtual void collide(std::shared_ptr<Entity> entity,GameData& gameData){};
    virtual void draw(float lerp_value){}
    virtual EntityType type(){return NONE;}

    Vector2 pos;
    Vector2 prevPos;
    Vector2 velocity;
    float hitboxRadius;
    bool zombie=false;
};
