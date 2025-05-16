#pragma once

#include "Screen.h"

#include "../UI/Button.h"

#include <raylib.h>
#include <vector>
#include "../score/ScoreService.h"

class LeaderboardScreen : public Screen {
    std::vector<Score> scores;
    Button exitButton;
    GameData& game;
    bool exitClicked = false;
    enum class Action {
        None,
        Exit
    };
    Action action = Action::None;
public:
    LeaderboardScreen(GameData& g);
    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
};