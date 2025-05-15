#include "CollisionSystem.h"
#include <vector>
#include <memory>
#include <raymath.h>
#include <algorithm>

bool CollisionSystem::areColliding(std::shared_ptr<Collider> col1, std::shared_ptr<Collider> col2){
    if(col1->type > col2->type){
        std::swap(col1, col2);
    }
    if(col1->type == Collider::Type::CIRCLE && col2->type == Collider::Type::CIRCLE){
        return CheckCollisionCircles(col1->p0, col1->radius, col2->p0, col2->radius);
    }
    if(col1->type == Collider::Type::CIRCLE && col2->type == Collider::Type::LINE_SEGMENT){
        return CheckCollisionCircleLine(col1->p0, col1->radius, col2->p0, col2->p1);
    }
    Vector2 collisionPoint;
    return CheckCollisionLines(col1->p0, col1->p1, col2->p0, col2->p1, &collisionPoint);
}

void CollisionSystem::handleCollisions(GameData& gameData){
    std::erase_if(colliders, [](const std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>>& ec){
        return ec.second.expired() || ec.first.expired();
    });
    
    for(auto ec1 : colliders){
        for(auto ec2 : colliders){
            if(ec1.first.lock() == ec2.first.lock() && ec1.second.lock() == ec2.second.lock())continue;
            if(areColliding(ec1.second.lock(), ec2.second.lock())){
                ec1.first.lock()->collide(ec1.second.lock(), ec2, gameData);
            }
        }
    }
}

void CollisionSystem::registerEntityCollider(std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> ec){
    colliders.push_back(ec);
}