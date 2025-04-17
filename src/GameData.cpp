#include "GameData.h"

#include "entities/Player.h"
#include "entities/SimpleEnemy.h"
#include "entities/SimpleSpawner.h"
#include "rand.h"

GameData::GameData()
{
    auto player = std::make_shared<Player>(Vector2{100.0, 100.0f},
                                           Vector2{100.0, 100.0f},
                                           Vector2{0.0f, 0.0f});
    this->player = player;
    registerEntity(player);

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

void GameData::gameUpdate(float dt)
{
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
