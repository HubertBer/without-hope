#include "GameData.h"

#include "entities/Player.h"
#include "entities/SimpleEnemy.h"

GameData::GameData()
{
    auto player = std::make_shared<Player>(Vector2{100.0, 100.0f},
                                           Vector2{100.0, 100.0f},
                                           Vector2{0.0f, 0.0f});
    this->player = player;
    registerEntity(player);

    for(int i = 0; i < 10; ++i){
        Vector2 pos = {(float)GetRandomValue(100, 1000), (float)GetRandomValue(100, 1000)};
        registerEntity(std::make_shared<SimpleEnemy>(
            pos,
            pos,
            Vector2{0, 0}
        ));
    }
}

void GameData::gameUpdate(float dt)
{
  for (auto entity : entities)
  {
    entity->gameUpdate(*this, dt);
  }
}

void GameData::physicsUpdate(){
    for(auto entity : entities){
        entity->physicsUpdate(*this);
    }
}

void GameData::draw(float lerp_value){
    for(auto entity : entities){
        entity->draw(lerp_value);
    }
}

void GameData::registerEntity(std::shared_ptr<Entity> entity){
    entities.push_back(entity);
}

Vector2 GameData::playerPos() const
{
    return player->pos;
}
