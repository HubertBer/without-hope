#include "Trail.h"
#include "raymath.h"
#include "../GameData.h"

Trail::Trail(std::weak_ptr<Entity> target, float thickness, float distance, Color color, bool dashed, bool contour, Color contourColor) 
    : Entity(Vector2Zero(), Vector2Zero(), Vector2Zero(), 0, 0, DrawingLayer::BLOOM),
      target(target),
      thickness(thickness),
      distance(distance),
      color(color),
      dashed(dashed),
      contour(contour),
      contourColor(contourColor)
    {}

void Trail::gameUpdate(GameData& game, float dt){
    for (int i = 0; i < MAX_POINTS; ++i){
        points[i].timer -= dt;
    }
}

void Trail::physicsUpdate(GameData&){
    if(target.expired()){
        fadeAwayTimer -= GameData::physicsDt;
        if(fadeAwayTimer < 0) {
            onDeath();
        }
        return;
    }
    const Vector2 tgtPos = target.lock()->pos;
    if(Vector2Length(tgtPos - lastPos) < distance){
        return;
    }

    for(int i = MAX_POINTS - 1; i >= 1; --i){
        points[i].pos = points[i - 1].pos;
        points[i].timer = points[i - 1].timer;
    }

    pointParity = !pointParity;
    points[0] = TrailPoint{
        tgtPos,
        LIFETIME,
    };

    lastPos = tgtPos;
}

void Trail::draw(){
    Vector2 pos0 = points[0].pos;
    if(!target.expired()){
        pos0 = target.lock()->pos;
    }

    for(int i = 0; i < MAX_POINTS; ++i){
        float timer = points[i].timer;
        if(timer <= 0){
            break;
        }
        Vector2 pos1 = points[i].pos;
        if(i >= IGNORE_POINTS && (!dashed || pointParity == (i % 2 == 1))){
            if (contour) {
                DrawLineEx(pos0, pos1, CONTOUR_THICKNESS_MOD * lerpThickness(timer), contourColor);    
            }
            DrawLineEx(pos0, pos1, lerpThickness(timer), color);
        }
        pos0 = pos1;
    }
}

float Trail::lerpThickness(float timer){
    return (timer / LIFETIME) * thickness;
}