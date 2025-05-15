#include "GameData.h"

#include "entities/Player.h"
#include "entities/SimpleEnemy.h"
#include "./scenes/GameScene.h"
#include "./score/ScoreService.h"
#include "raymath.h"
#include "UI/Scaler.h"
#include <algorithm>

GameData::GameData(const std::string* playerName):playerName(playerName)
{
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

Rectangle GameData::getCameraVisionBoundaries(Camera2D camera){
    // Vector2 origin = mainCamera.offset + mainCamera.target;
    Vector2 origin = {
        camera.target.x - (camera.offset.x / camera.zoom),
        camera.target.y - (camera.offset.y / camera.zoom)
    };
        
    return Rectangle{
        origin.x,
        origin.y,
        GetScreenWidth() / camera.zoom,
        GetScreenHeight() / camera.zoom
    };
}

bool GameData::gameUpdate(float dt, float lerpValue)
{
    for(auto entity: entitiesBuffer){
        entities.push_back(entity);
    }
    entitiesBuffer.clear();
    this->lerpValue = lerpValue;
    scoreKeeper.passiveAdd(dt);
    handleCollisions();
    if(player->zombie){
        return true;
    }
    for (auto entity : entities)
    {
        entity->gameUpdate(*this, dt);
    }
    deleteZombieEntities();
    return false;
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
    collisionSystem.handleCollisions(entities,*this);
}

void GameData::deleteZombieEntities(){
    for(auto& entity : entities){
        if(entity->zombie)kill(entity);
    }
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
}

void GameData::kill(std::shared_ptr<Entity> entity){
    timeSinceKill = GetTime();
    scoreKeeper.killEntityAdd(entity);
}

float GameData::getTimeSinceKill() {
  return timeSinceKill;
}

Vector2 GameData::playerPos() const {
    return player->pos;
}

void GameData::reset(GameData& gameData) {
    const std::string* playerName = gameData.playerName;
    GameData* ptr = &gameData;
    ptr->~GameData();
    new (ptr) GameData(playerName);
}

void GameData::saveScore(){
    ScoreService::saveScore({scoreKeeper.getScore(),*playerName});
}

int GameData::getScore(){
    return scoreKeeper.getScore();
}

Rectangle GameData::getMapBoundaries(){
    return mapBoundaries;
}

GameData::~GameData(){
    saveScore();
}