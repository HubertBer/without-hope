#pragma once
#include "../entities/SimpleEnemy.h"


class ScoreKeeper{
    public:
    void passiveAdd(float dt);
    void killEntityAdd(Entity& entity);
    int getScore();
    private:
    int score=0;
    float residue=0.f;
};