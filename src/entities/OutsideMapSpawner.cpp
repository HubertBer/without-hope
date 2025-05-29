#include "OutsideMapSpawner.h"
#include "raymath.h"
#include "../rand.h"
#include "SimpleEnemy.h"
#include "Squadron.h"

OutsideMapSpawner::OutsideMapSpawner(Vector2 delay) : Entity(Vector2Zero(), Vector2Zero(), Vector2Zero(), 0), delay{delay} {}

void OutsideMapSpawner::gameUpdate(GameData& game, float dt){
    timer -= dt;
    if(timer < 0){
        timer += GetRandomFloat(delay.x, delay.y);

        Rectangle map = game.getMapBoundaries();
        Rectangle rect[4] = {
            Rectangle{map.x - 150, map.y - 100, 100, map.height + 200},
            Rectangle{map.x + map.width + 50, map.y - 100, 100, map.height + 200},
            Rectangle{map.x - 100, map.y - 150, map.width + 200, 100},
            Rectangle{map.x - 100, map.y + map.height + 50, map.width + 200, 100}
        };

        Rectangle area = rect[GetRandomValue(0, 3)];
        Vector2 pos{
            GetRandomFloat(area.x, area.x + area.width),
            GetRandomFloat(area.y, area.y + area.height)
        };
        
        if(GetRandomFloat(0, 1) < pSquadron){
            game.registerEntity(std::make_shared<Squadron>(
                pos,
                0
            ));
        }else{
            game.registerEntity(std::make_shared<SimpleEnemy>(
                pos,
                pos,
                Vector2{0,0}
            ));
        }
    }
}

EntityType OutsideMapSpawner::type(){
    return EntityType::SIMPLE_SPAWNER;
}