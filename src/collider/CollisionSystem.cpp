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
        if(col1.type == ColliderType::CIRCLE && col2.type == ColliderType::CIRCLE){
            return CheckCollisionCircles(col1.p0, col1.radius, col2.p0, col2.radius);
        }
        if(col1.type == ColliderType::CIRCLE && col2.type == ColliderType::LINE_SEGMENT){
            return CheckCollisionCircleLine(col1.p0, col1.radius, col2.p0, col2.p1);
        }
        if(col1.type == ColliderType::CIRCLE && col2.type == ColliderType::CIRCLE_OUTLINE){
            return CheckCollisionCircleOutlineCircle(col2.p0, col2.radius, col2.inside_radius, col1.p0, col1.radius);
        }
        if(col1.type == ColliderType::LINE_SEGMENT && col2.type == ColliderType::LINE_SEGMENT){
            Vector2 collisionPoint;
            return CheckCollisionLines(col1.p0, col1.p1, col2.p0, col2.p1, &collisionPoint);
        }else{
            //I know that its dengerous, but I don't think we need that right now (only slow circle is circle outline, and enemies are always circles)
            //correct me if im wrong 
            return false;
        }
    }
}

std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> GetCollisions(const std::list<std::shared_ptr<Entity>>& entities){
    std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> collisions;
    
    for(auto e1 : entities){
        if(e1->collider.type == ColliderType::NONE){
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