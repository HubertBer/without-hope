#include "TargetableCamera.h"
#include "raymath.h"
#include "raylib.h"
#include "../GameData.h"

TargetableCamera::TargetableCamera(std::shared_ptr<Entity> target)
: Entity(target->pos, target->pos, {0, 0}, 0){
    this->posNow = target->pos;
    this->target = target;
}

void TargetableCamera::gameUpdate(GameData& game, float dt){
    this->posNow = target->posNow + Vector2{
        target->hitboxRadius,
        target->hitboxRadius
    };

    Camera2D camera = game.getMainCamera();
    camera.target = posNow +  Vector2{ 
        target->hitboxRadius,
        target->hitboxRadius 
    };

    game.setMainCamera(camera);
}

void TargetableCamera::physicsUpdate(GameData& game){}
void TargetableCamera::collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData){}
void TargetableCamera::draw(){}

EntityType TargetableCamera::type(){
    return TARGETABLE_CAMERA;
}