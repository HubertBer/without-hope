#include "SquadronShip.h"
#include "raylib.h"
#include "raymath.h"
#include "../GameData.h"

SquadronShip::SquadronShip(Vector2 pos, float rotation)
    :Entity(pos, pos, Vector2Zero(), RADIUS, rotation){
    
    // TODO_IDEA:
    // Change this ship texture to other, I think that triangle could be nice for this desing
    // probably need to take care of rotation then...
    loadTexture("square.png", 0.3f);
    loadShader("bloom");
    collider = MakeCircleCollider(pos, RADIUS);
}

void SquadronShip::setTarget(Vector2 target){
    this->target = target;
}

void SquadronShip::gameUpdate(GameData& game, float dt){
    posNow = game.lerp(prevPos, pos);
}

void SquadronShip::physicsUpdate(GameData& game){
    prevPos = pos;
    collider.p0 = pos;
    
    if(Vector2Length(game.playerPos() - pos) < FUCK_IT_DISTANCE){
        fuckIt = true;
    }

    Vector2 dir = target - pos;
    if(fuckIt){
        dir = game.playerPos() - pos;
    }

    // TODO_IDEA:
    // Movement looks bad sometimes - it stutters, probably because of this if
    // I believe that the best idea is to add acceleration and change don't change velocity manually
    // Add it after merging weapon changes as they also have acceleration change to player
    // and it can be unified and extracted to Entity method as we probably want it everywhere.
    if(Vector2Length(dir) <  MAX_SPEED * GameData::physicsDt){
        pos = target;
    }else{
        dir = Vector2Normalize(dir);
        velocity = dir * MAX_SPEED;
        pos += velocity * GameData::physicsDt;
    }

    if(Vector2Length(pos - prevPos) > EPSILON){
        rotation = Vector2Angle(Vector2{1, 0}, (pos - prevPos));
    }
}

void SquadronShip::draw(){
    drawTexture();
    
    // Debug circle on target position
    // DrawCircle(target.x, target.y, 8.f, BLACK);
}

void SquadronShip::collide(std::shared_ptr<Entity> entity, GameData& gameData){
    switch(entity->type()){
        case SIMPLE_BULLET:
        case ELECTRIC_FENCE:
            onDeath();
    }
}

EntityType SquadronShip::type(){
    return SQUADRON_SHIP;
}