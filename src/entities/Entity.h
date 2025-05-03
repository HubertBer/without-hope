#pragma once

#include <raylib.h>
#include <memory>
#include <iostream>

class GameData;

enum EntityType{
    NONE,
    PLAYER,
    SIMPLE_ENEMY,
    SIMPLE_BULLET,
    SIMPLE_SPAWNER,
};

class Entity{
public:
    Entity(Vector2 prevPos, Vector2 pos, Vector2 velocity,float hitboxRadius, float rotation=0)
        : prevPos(prevPos), pos(pos), velocity(velocity),hitboxRadius(hitboxRadius), rotation(rotation) {}
    /// @brief Function called every physics tick.
    /// @param  
    virtual void physicsUpdate(GameData&){}
    /// @brief Function called every frame. Put game logic here.
    /// @param game 
    /// @param dt 
    virtual void gameUpdate(GameData& game, float dt){}
    virtual void collide(std::shared_ptr<Entity> entity,GameData& gameData){};
    virtual void draw(){}
    void drawTexture();
    virtual EntityType type(){return NONE;}

    Vector2 pos;
    Vector2 prevPos;
    Vector2 posNow;
    Vector2 velocity;
    // The angle of the entity in degrees (raylib requirement).
    float rotation=0;
    float hitboxRadius;
    bool zombie=false;
protected:
    void loadTexture(const std::string& path, float scale = 1.f);
    void loadShader(const std::string& path);

private:
    Texture2D texture;
    Shader shader;
    bool useShader=false;
};
