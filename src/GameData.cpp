#include "GameData.h"

#include "entities/Player.h"
#include "entities/SimpleEnemy.h"
#include "./scenes/GameScene.h"
#include "./score/ScoreService.h"
#include "raymath.h"
#include "UI/Scaler.h"
#include <algorithm>
#include "collider/CollisionSystem.h"

GameData::GameData(const std::string* playerName):playerName(playerName)
{
    hasEnded=false;
    LoadGameScene(*this);
}

Vector2 GameData::lerp(Vector2 v1, Vector2 v2){
    return v1 + (v2 - v1) * lerpValue; 
}

float GameData::lerp(float v1, float v2)
{
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

Rectangle GameData::getCameraVisionBoundaries(Camera2D camera) {
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

std::unordered_map<DrawingLayer, std::vector<std::shared_ptr<Entity>>> GameData::prepareDraw()
{
    std::unordered_map<DrawingLayer, std::vector<std::shared_ptr<Entity>>> drawLayers;

    entities.sort([](const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2){
        return e1->drawOrder() < e2->drawOrder();
    });
    for(auto entity : entities){
        drawLayers[entity->drawLayer].push_back(entity);
    }
    return drawLayers;
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
    auto collisions = GetCollisions(entities);
    for(auto[e1, e2] : collisions){
        e1->collide(e2, *this);
    }
}

void GameData::deleteZombieEntities(){
    for(auto& entity : entities){
        if(entity->zombie)kill(entity);
    }
    entities.remove_if([](std::shared_ptr<Entity> x){return x->zombie;});
}

void GameData::physicsUpdate(){
    player->physicsUpdate(*this);
    for(auto entity : entities){
        if (entity != player) {
            entity->physicsUpdate(*this);
        }
    }
}

void GameData::registerEntity(std::shared_ptr<Entity> entity){
    entitiesBuffer.push_back(entity);
    entity->start(*this);
}

void GameData::kill(std::shared_ptr<Entity> entity){
    timeSinceKill = GetTime();
    scoreKeeper.killEntityAdd(entity);
}

float GameData::getTimeSinceKill() {
  return timeSinceKill;
}

float GameData::getLastDamageTime()
{
    return std::dynamic_pointer_cast<Player>(player)->timeOfLastDamage;
}

Vector2 GameData::playerPos() const {
    return player->pos;
}

Vector2 GameData::playerVelocity() const {
    return player->velocity;
}

void GameData::reset(GameData& gameData) {
    const std::string* playerName = gameData.playerName;
    GameData* ptr = &gameData;
    ptr->~GameData();
    new (ptr) GameData(playerName);
}
void GameData::endGame(){
    hasEnded=true;
    saveScore();
}

void GameData::saveScore(){
    scorePosition = ScoreService::saveScore({scoreKeeper.getScore(),*playerName});
}

int GameData::getScore(){
    return scoreKeeper.getScore();
}

Rectangle GameData::getMapBoundaries() {
    return mapBoundaries;
}

std::vector<std::shared_ptr<Entity>> GameData::entitiesOfType(EntityType type) {
    std::vector<std::shared_ptr<Entity>> ret;
    for(auto e : entities) {
        if (e->type() == type) {
            ret.push_back(e);
        }
    }

    return ret;
}