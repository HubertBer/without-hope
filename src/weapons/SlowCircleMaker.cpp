#include "SlowCircleMaker.hpp"
#include "../entities/Player.h"
#include "raymath.h"
#include "../entities/SlowCircle.h"

SlowCircleMaker::SlowCircleMaker(){}

void SlowCircleMaker::gameUpdate(GameData& game, Player& player, float dt){
    timer -= dt;
    if(timer < 0 && IsKeyDown(KEY_SPACE)){
        game.registerEntity(std::make_shared<SlowCircle>(MakeCircleOutlineCollider(player.pos, 0.0f,0.0f)));
        timer = cooldown;
    }
}

void SlowCircleMaker::physicsUpdate(GameData& game, Player& player){
    
}