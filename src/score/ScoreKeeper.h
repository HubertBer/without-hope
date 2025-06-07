#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../entities/Entity.h"

class ScoreKeeper{
    public:
    void passiveAdd(float dt);
    void killEntityAdd(std::shared_ptr<Entity> entity);
    int getScore();
    private:
    int score=0;
    float residue=0.f;
    inline static const std::string SCORE_FILE ="scores/high_scores"; 
    static constexpr int LEADERBOARD_SIZE =10;
};
