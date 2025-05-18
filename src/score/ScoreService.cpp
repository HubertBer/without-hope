#include "ScoreService.h"
#include "../nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

std::vector<Score> ScoreService::loadLeaderboard(){
    std::vector<Score> scores;
    std::ifstream file(SCORE_FILE);
    if (file.is_open()) {
        json j;
        file >> j;
        if (j.contains("highscores") && j["highscores"].is_array()) {
            for (const auto& s : j["highscores"]) {
                scores.push_back({ s["score"],s["name"] });
            }
        }
        file.close();
    }
    return scores;


}


int ScoreService::saveScore(Score currentScore){
    if(currentScore.result==0) return -1;
    std::vector<Score> scores = loadLeaderboard();

    int position = std::upper_bound(scores.begin(),scores.end(),currentScore,std::greater<Score>()) - scores.begin();
    scores.push_back(currentScore);
    std::sort(scores.begin(), scores.end(),std::greater<Score>());

    if(scores.size()>LEADERBOARD_SIZE){
        scores.resize(LEADERBOARD_SIZE);
    }

    json j;
    for (auto& entry : scores) {
        j["highscores"].push_back({ {"score", entry.result},{"name",entry.playerName} });
    }

    std::ofstream file(SCORE_FILE);
    if (file.is_open()) {
        file << j.dump();
        file.close();
    }
    if(position<10)return position;
    return -1;

}