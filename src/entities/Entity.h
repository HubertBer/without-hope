#pragma once

#include <raylib.h>
#include <memory>
#include <iostream>
#include "../collider/Collider.h"
#include "../collider/CollisionSystem.h"
#include "EntityType.h"

class GameData;
class Collider;

enum DrawingLayer : uint16_t{
    BACKGROUND = 0,
    DEFAULT,
    FOREGROUND,
};

class Entity{
public:
    Entity(Vector2 prevPos, Vector2 pos, Vector2 velocity, float hitboxRadius, float rotation=0, DrawingLayer drawLayer = DEFAULT)
        : prevPos(prevPos), pos(pos), velocity(velocity),hitboxRadius(hitboxRadius), rotation(rotation), drawLayer(drawLayer) {}
    /// @brief Function called every physics tick.
    /// @param  
    virtual void physicsUpdate(GameData&){}
    /// @brief Function called every frame. Put game logic here.
    /// @param game 
    /// @param dt 
    virtual void gameUpdate(GameData& game, float dt){}
    virtual void collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData){};
    virtual void draw(){}
    void drawTexture();
    virtual EntityType type(){return NONE;}
    virtual std::pair<DrawingLayer, float> drawOrder(){return {drawLayer, pos.y};};
    virtual void start(GameData&){}

    Vector2 pos;
    Vector2 prevPos;
    Vector2 posNow;
    Vector2 velocity; 
    // The angle of the entity in degrees (raylib requirement).
    float rotation=0;
    DrawingLayer drawLayer{DEFAULT};
    float hitboxRadius;
    bool zombie=false;
protected:
    void loadTexture(const std::string& path, float scale = 1.f);
    void loadShader(const std::string& path);
    std::weak_ptr<Entity> self;
    friend class GameData;

private:
    Texture2D texture;
    Shader shader;
    bool useShader=false;
};
