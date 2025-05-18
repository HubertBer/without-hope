#include "Trail.h"
#include "raymath.h"

Trail::Trail(std::weak_ptr<Entity> target)
    :Entity(Vector2Zero(), Vector2Zero(), Vector2Zero(), 0, 0, DrawingLayer::BLOOM),
    target(target){}

void Trail::gameUpdate(GameData&, float dt){
    for (int i = 0; i < MAX_POINTS; ++i){
        points[i].timer -= dt;
    }
}

void Trail::physicsUpdate(GameData&){
    if(target.expired()){
        onDeath();
        return;
    }
    const Vector2 tgtPos = target.lock()->pos;
    if(Vector2Length(tgtPos - lastPos) < DISTANCE){
        return;
    }

    for(int i = MAX_POINTS - 1; i >= 1; --i){
        points[i].pos = points[i - 1].pos;
        points[i].timer = points[i - 1].timer;
    }

    points[0] = TrailPoint{
        tgtPos,
        LIFETIME,
    };

    lastPos = tgtPos;
}

void Trail::draw(){
    if(target.expired()){
        onDeath();
        return;
    }
    Vector2 pos0 = target.lock()->pos;

    for(int i = 0; i < MAX_POINTS; ++i){
        float timer = points[i].timer;
        if(timer <= 0){
            break;
        }
        Vector2 pos1 = points[i].pos;
        if(i >= IGNORE_POINTS){
            DrawLineEx(pos0, pos1, lerpThickness(timer), color);
        }
        pos0 = pos1;
    }
}

float Trail::lerpThickness(float timer){
    return (timer / LIFETIME) * THICKNESS;
}