#include "CollisionSystem.h"

#include <vector>
#include <memory>
#include <raymath.h>


bool CollisionSystem::areColliding(std::shared_ptr<Entity> first,std::shared_ptr<Entity> second){
    //should we abstract even further?
    return CheckCollisionCircles(first->pos,first->hitboxRadius,second->pos,second->hitboxRadius);
}

void CollisionSystem::handleCollisions(std::vector<std::shared_ptr<Entity>>& entities){
    for(auto entity1 : entities){
        for(auto entity2 : entities){
            if(entity1 == entity2)continue;
            if(areColliding(entity1,entity2)){
                entity1->collide(entity2);
                entity2->collide(entity1);
            }
        }
    }
}