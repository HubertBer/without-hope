#include "CollisionSystem.h"
#include <vector>
#include <memory>
#include <algorithm>
#include "../entities/Entity.h"
#include <list>

namespace{
    bool AreColliding(Collider col1, Collider col2){
        if(col1.type > col2.type){
            std::swap(col1, col2);
        }
        if(col1.type == Collider::Type::CIRCLE && col2.type == Collider::Type::CIRCLE){
            return CheckCollisionCircles(col1.p0, col1.radius, col2.p0, col2.radius);
        }
        if(col1.type == Collider::Type::CIRCLE && col2.type == Collider::Type::LINE_SEGMENT){
            return CheckCollisionCircleLine(col1.p0, col1.radius, col2.p0, col2.p1);
        }
        Vector2 collisionPoint;
        return CheckCollisionLines(col1.p0, col1.p1, col2.p0, col2.p1, &collisionPoint);
    }
}

std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> GetCollisions(const std::list<std::shared_ptr<Entity>>& entities){
    std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> collisions;
    
    for(auto e1 : entities){
        if(e1->collider.type == Collider::Type::NONE){
            continue;
        }
        for(auto e2 : entities){
            if(e1 == e2){
                continue;
            }       

            if(AreColliding(e1->collider, e2->collider)){
                collisions.push_back({e1, e2});
            }
        }
    }

    return collisions;
}