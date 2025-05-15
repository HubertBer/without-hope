#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../collider/Collider.h"

class SimpleEnemy : public Entity{
public:
    SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData) override;
    void draw() override;
    void start(GameData&) override;
    EntityType type() override;
    virtual int getScore() override{return score;}

private:
    std::shared_ptr<Collider> collider;

    static constexpr float BASE_RADIUS =10.f;
    static constexpr float maxSpeed = 300.f;
    static constexpr int score = 10;
    
};