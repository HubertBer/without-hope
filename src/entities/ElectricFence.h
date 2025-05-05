#pragma once

#include "Entity.h"
#include "../GameData.h"

class ElectricFence : public Entity{
public:
    ElectricFence(std::shared_ptr<Collider> collider);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData) override;
    void draw() override;
    void start(GameData&) override;
    EntityType type() override;

private:
    std::shared_ptr<Collider> collider;
    const Color color = SKYBLUE;
    const float width = 10.0f;
};