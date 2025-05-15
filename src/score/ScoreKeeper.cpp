#include "ScoreKeeper.h"

void ScoreKeeper::passiveAdd(float dt){
    score += static_cast<int>(residue += dt);
    residue -= static_cast<int>(residue);
    
}

void ScoreKeeper::killEntityAdd(std::shared_ptr<Entity> entity){
    score += entity->getScore();
}

int ScoreKeeper::getScore(){
    return score;
}

