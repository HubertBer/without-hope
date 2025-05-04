#pragma once

#include "raylib.h"
#include "Entity.h"
#include <memory>

class TargetableCamera : public Entity{
public:
    TargetableCamera(std::shared_ptr<Entity> target);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData) override;
    void draw() override;
    EntityType type() override;

private:
    std::shared_ptr<Entity> target;
};