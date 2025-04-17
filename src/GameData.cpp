#include "GameData.h"

#include "entities/Player.h"
#include "entities/SimpleEnemy.h"
#include "./scenes/GameScene.h"

GameData::GameData()
{
    LoadGameScene(*this);
}

void GameData::gameUpdate(float dt)
{
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
    collisionSystem.handleCollisions(entities,*this);
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
    for(auto entity : entities){
        entity->draw();
    }
}

void GameData::registerEntity(std::shared_ptr<Entity> entity){
    entitiesBuffer.push_back(entity);
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