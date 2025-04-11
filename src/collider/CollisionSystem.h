#pragma once

#include <vector>
#include <memory>

#include "../entities/Entity.h"

class Entity;

class CollisionSystem{
    public:
    void handleCollisions(std::vector<std::shared_ptr<Entity>>& entitites);
    bool areColliding(std::shared_ptr<Entity> first,std::shared_ptr<Entity> second);
};