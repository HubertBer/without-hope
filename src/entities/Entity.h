#pragma once

#include <raylib.h>
#include <memory>
#include <iostream>
#include "../collider/Collider.h"
#include "EntityType.h"

class GameData;

enum class DrawingLayer : uint16_t{
    BACKGROUND = 0,
    DEFAULT,
    BLOOM,
    FOREGROUND,
};

class Entity{
public:
    Entity(Vector2 prevPos, Vector2 pos, Vector2 velocity, float hitboxRadius, float rotation=0, DrawingLayer drawLayer = DrawingLayer::DEFAULT)
        : prevPos(prevPos), pos(pos), velocity(velocity),hitboxRadius(hitboxRadius), rotation(rotation), drawLayer(drawLayer) {}
    /// @brief Function called every physics tick.
    /// @param  
    virtual void physicsUpdate(GameData&){}
    /// @brief Function called every frame. Put game logic here.
    /// @param game 
    /// @param dt 
    virtual void gameUpdate(GameData& game, float dt){}
    virtual void collide(std::shared_ptr<Entity> other, GameData& gameData){};
    virtual void draw(){}
    void drawTexture();
    virtual EntityType type(){return NONE;}
    virtual std::pair<DrawingLayer, float> drawOrder(){return {drawLayer, pos.y};};
    void onDeath();
    virtual int getScore(){return score;}

    virtual void start(GameData&){}

    Vector2 pos;
    Vector2 prevPos;
    Vector2 posNow;
    Vector2 velocity; 
    Collider collider;
    // The angle of the entity in degrees (raylib requirement).
    float rotation=0;
    DrawingLayer drawLayer{DrawingLayer::DEFAULT};
    float hitboxRadius;
    bool zombie=false;
    static constexpr int score=0;
protected:
    /// @brief Load a texture and attach it to the entity. 
    /// @param fileName The name of the file to load from the sprites/ folder, e.g. "player.png"
    /// @param scale 
    void loadTexture(const std::string& fileName, float scale = 1.f);
    /// @brief Load a shader and attach it to the entity.
    /// @param name The name of the shader without the .fs extension, e.g. "voronoi"
    void loadShader(const std::string& name);
    Color textureTint = WHITE;

private:

    Texture2D texture;
    Shader shader;
    bool useShader=false;
};
