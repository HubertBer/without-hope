#include "ElectricFenceMaker.hpp"
#include "../entities/Player.h"
#include "raymath.h"
#include "../entities/ElectricFence.h"

ElectricFenceMaker::ElectricFenceMaker(){}

void ElectricFenceMaker::gameUpdate(GameData& game, Player& player, float dt){
    if(placing && IsKeyPressed(KEY_SPACE)){
        placing = false;
        electricFence.reset();
        timer = cooldown;
    }
    if(placing){
        return;
    }
    timer -= dt;
    if(timer < 0 && IsKeyDown(KEY_SPACE)){
        placing = true;
        Collider fenceCollider = MakeLineCollider(player.pos, player.pos);
        electricFence = std::make_shared<ElectricFence>(fenceCollider);
        game.registerEntity(electricFence);
    }
}

void ElectricFenceMaker::physicsUpdate(GameData& game, Player& player){
    if(!placing){
        return;
    }

    Collider& fenceCollider = electricFence->collider;
    fenceCollider.p1 = player.pos;

    if(Vector2Length({fenceCollider.p1 - fenceCollider.p0}) > maxFenceLength){
        fenceCollider.p1 = fenceCollider.p0 + Vector2Normalize(fenceCollider.p1 - fenceCollider.p0) * maxFenceLength;
        placing = false;
        electricFence.reset();
        timer = cooldown;
    }
}