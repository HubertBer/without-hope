#include "TargetableCamera.h"
#include "raymath.h"
#include "raylib.h"
#include "../GameData.h"

#include <algorithm>
#include <iostream>

TargetableCamera::TargetableCamera(std::shared_ptr<Entity> target)
: Entity(target->pos, target->pos, {0, 0}, 0){
    this->posNow = target->pos;
    this->target = target;
}

 void TargetableCamera::gameUpdate(GameData& game, float dt){
    this->prevPos = this->pos;

    Rectangle mapBoundaries = game.getMapBoundaries();

    Vector2 cameraPos = target->posNow + Vector2 {
        target->hitboxRadius,
        target->hitboxRadius
    };
    Camera2D camera = game.getMainCamera();
    camera.target = cameraPos;
    Rectangle cameraBoundaries = GameData::getCameraVisionBoundaries(camera);
 
    float offset = 100.0f;
    cameraPos.x = (cameraBoundaries.x + offset) < mapBoundaries.x ? prevPos.x : cameraPos.x;
    cameraPos.x = (cameraBoundaries.x + cameraBoundaries.width - offset) > mapBoundaries.x + mapBoundaries.width ? prevPos.x : cameraPos.x;
    cameraPos.y = (cameraBoundaries.y + offset) < mapBoundaries.y ? prevPos.y : cameraPos.y;
    cameraPos.y = (cameraBoundaries.y + cameraBoundaries.height - offset) > mapBoundaries.y + mapBoundaries.height ? prevPos.y : cameraPos.y;
 
    this->pos = cameraPos;
    camera.target = cameraPos;
    game.setMainCamera(camera);
}