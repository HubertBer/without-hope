#pragma once

#include <list>
#include <memory>

#include "../entities/Entity.h"


class CollisionSystem{
    public:
    void handleCollisions(std::list<std::shared_ptr<Entity>>& entitites,GameData& gameData);
    bool areColliding(std::shared_ptr<Entity> first,std::shared_ptr<Entity> second);
};