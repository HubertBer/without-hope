#pragma once

#include <memory>
#include <vector>

#include "../entities/Entity.h"
#include "Collider.h"
#include "../GameData.h"

class Entity;
class GameData;
class Collider;

class CollisionSystem{
public:
    void handleCollisions(GameData& gameData);
    void registerEntityCollider(std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> ec);
private:
    bool areColliding(std::shared_ptr<Collider> ec1, std::shared_ptr<Collider> ec2);
    std::vector<std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>>> colliders;
};