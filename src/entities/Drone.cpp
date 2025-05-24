#include "Drone.h"
#include "raylib.h"
#include "raymath.h"
#include "../GameData.h"

Drone::Drone(Vector2 pos, float angle) 
    :Entity(pos, pos, Vector2Zero(), BASE_RADIUS, 0, DrawingLayer::BLOOM){
    collider = MakeCircleCollider(pos, hitboxRadius);
}

void Drone::gameUpdate(GameData& game, float dt) {
    posNow = game.lerp(prevPos, pos);
}

void Drone::physicsUpdate(GameData& game) {
    prevPos = pos;
    angle += ANGULAR_SPEED * GameData::physicsDt;
    if(angle > 180) {
        angle -= 360;
    }
    // figure out a way for a nice variable offset either something like this or maybe acceleration/velocity for the drone.
    Vector2 target_pos = game.playerPos() + Vector2Rotate(OFFSET, angle * DEG2RAD) - Vector2Normalize(game.playerVelocity()) * 30.f;
    Vector2 dir = target_pos - pos;
    if (Vector2Length(dir) < MAX_SPEED * GameData::physicsDt) {
        pos = target_pos;
        velocity = {0};
    } else {
        velocity = Vector2Normalize(dir) * MAX_SPEED;
    }
    // if(Vector2Length(dir) < EPSILON) {
    //     acceleration = Vector2Zero();
    // } else {
    //     acceleration = Vector2Normalize(dir) * MAX_ACCELERATION;  
    // }


    // velocity += acceleration * GameData::physicsDt;
    pos += velocity * GameData::physicsDt;
    
    collider.p0 = pos;
}

void Drone::collide(std::shared_ptr<Entity> other, GameData& gameData) {
    if (other->type() == ENEMY) {
        onDeath();
    }
}

void Drone::draw() {
    DrawCircle(posNow.x, posNow.y, hitboxRadius, color); 
}

EntityType Drone::type() {
    return PLAYER;
}