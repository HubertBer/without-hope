#pragma once

#include <raylib.h>

#include "Entity.h"

class SimpleEnemy : public Entity{
public:
    SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> entity,GameData& gameData) override;
    void draw(float lerpValue) override;
    EntityType type() override;


private:
    static constexpr float BASE_RADIUS =10.f;
    static constexpr float maxSpeed = 300.f;
    
};