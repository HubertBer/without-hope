#include "GameData.h"

#include "entities/Player.h"
#include "entities/SimpleEnemy.h"
#include "./scenes/GameScene.h"
#include "raymath.h"
#include "UI/Scaler.h"
#include <algorithm>

GameData::GameData()
{
    collisionSystem = std::make_shared<CollisionSystem>();
    LoadGameScene(*this);
}

Vector2 GameData::lerp(Vector2 v1, Vector2 v2){
    return v1 + (v2 - v1) * lerpValue; 
}

Camera2D GameData::getMainCamera() const {
    return mainCamera;
}

void GameData::setMainCamera(Camera2D camera){
    mainCamera = camera;
}

Vector2 GameData::getMouseWorldPosition() const {
    return GetScreenToWorld2D(getVirtualPosition(GetMousePosition()), mainCamera);
}

Rectangle GameData::getCameraVisionBoundaries() const{
    // Vector2 origin = mainCamera.offset + mainCamera.target;
    Vector2 origin = {
        mainCamera.target.x - (mainCamera.offset.x / mainCamera.zoom),
        mainCamera.target.y - (mainCamera.offset.y / mainCamera.zoom)
    };
        
    return Rectangle{
        origin.x,
        origin.y,
        GetScreenWidth() / mainCamera.zoom,
        GetScreenHeight() / mainCamera.zoom
    };
}

void GameData::gameUpdate(float dt, float lerpValue)
{
    this->lerpValue = lerpValue;
    handleCollisions();
    if(player->zombie){
        resetGame();
        return; 
    }
    for (auto entity : entities)
    {
        entity->gameUpdate(*this, dt);
    }
    for(auto entity: entitiesBuffer){
        entities.push_back(entity);
    }
    entitiesBuffer.clear();
    deleteZombieEntities();
}

bool GameData::checkPresent(EntityType type){
    for(auto entity: entities){
        if(entity->type()==type)return true;
    }
    return false;
}

void GameData::setPlayer(std::shared_ptr<Entity> player){
    this->player = player;
}

void GameData::handleCollisions(){
    collisionSystem->handleCollisions(*this);
}

void GameData::deleteZombieEntities(){
    entities.remove_if([](std::shared_ptr<Entity> x){return x->zombie;});
}

void GameData::physicsUpdate(){
    for(auto entity : entities){
        entity->physicsUpdate(*this);
    }
}

void GameData::draw(){
    entities.sort([](const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2){
        return e1->drawOrder() < e2->drawOrder();
    });
    for(auto entity : entities){
        entity->draw();
    }
}

void GameData::registerEntity(std::shared_ptr<Entity> entity){
    entitiesBuffer.push_back(entity);
    entity->self = entity;
    entity->start(*this);
}

void GameData::registerEntityCollider(std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> ec){
    collisionSystem->registerEntityCollider(ec);
}

void GameData::kill() {
    timeSinceKill = GetTime();
}

float GameData::getTimeSinceKill() {
  return timeSinceKill;
}

Vector2 GameData::playerPos() const {
    return player->pos;
}

void GameData::resetGame(){
    entities.clear();
    entitiesBuffer.clear();
    
    LoadGameScene(*this);
}