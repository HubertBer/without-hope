#pragma once

#include <vector>
#include <string>
class Score{
    public:
    int result;
    std::string playerName;
    Score():result(0){};
    Score(int x,std::string name):result(x){
        if(name.empty())name = defaultName;
        playerName = name;
    };

    friend bool operator<(const Score& a, const Score&b){
        return a.result<b.result;
    };
    inline static const std::string defaultName = "Anonymous";
};

class ScoreService{
    public:
    static int saveScore(Score score);
    static std::vector<Score> loadLeaderboard();
    private:
    inline static const std::string SCORE_FILE ="scores/high_scores"; 
    static constexpr int LEADERBOARD_SIZE = 9;
};
