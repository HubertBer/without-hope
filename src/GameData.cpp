#include "GameData.h"

#include "entities/Player.h"
#include "entities/SimpleEnemy.h"
#include "entities/SimpleSpawner.h"
#include "entities/TargetableCamera.h"
#include "entities/GridBackground.h"
#include "rand.h"
#include "raymath.h"
#include "UI/Scaler.h"
#include <algorithm>

GameData::GameData()
{
    collisionSystem = std::make_shared<CollisionSystem>();

    auto player = std::make_shared<Player>(Vector2{100.0, 100.0f},
                                           Vector2{100.0, 100.0f},
                                           Vector2{0.0f, 0.0f});
    this->player = player;
    registerEntity(player);

    auto targetableCamera = std::make_shared<TargetableCamera>(player);
    registerEntity(targetableCamera);

    auto gridBg = std::make_shared<GridBackground>();
    registerEntity(gridBg);

    for(int i = 0; i < 10; ++i){
        Vector2 pos = {GetRandomFloat(300, 1000), GetRandomFloat(300, 1000)};
        registerEntity(std::make_shared<SimpleEnemy>(
            pos,
            pos,
            Vector2{0, 0}
        ));
    }

    registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{0, 0, 100, 100},
        3,
        6
    ));

    registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{1000, 1000, 100, 100},
        3,
        6
    ));
    
    registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{1000, 0, 100, 100},
        3,
        6
    ));
    
    registerEntity(std::make_shared<SimpleSpawner>(
        Rectangle{0, 1000, 100, 100},
        3,
        6
    ));
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
  if(player->zombie) return;//placeholder, we should end the game
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
