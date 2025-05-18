#include "LeaderboardScreen.h"
#include "../Config.h"

LeaderboardScreen::LeaderboardScreen(GameData& g)
    : Screen(), game(g) {
    int w = 200, h = 60, spacing = 20;
    float startY = (Config::screenHeight - h * 2 );

    exitButton = createButton((Config::screenWidth - w) / 2.0f, startY, w, h, "MAIN MENU");
}

void LeaderboardScreen::update(float dt) {
    (void)dt;
    if (isButtonClicked(exitButton)) action = Action::Exit;
}

void LeaderboardScreen::draw() {
    ClearBackground(GRAY);
    drawButton(exitButton);
    int currY = 100;
    int fontSize=(Config::screenHeight -2*60)/12;
    int w = 300;
    int w_number=70,spacing=6;
    for(auto& score:ScoreService::loadLeaderboard()){
        DrawTextStretched(score.playerName.c_str(),(Config::screenWidth - w) / 2.0f,currY,fontSize,BLACK);
        DrawTextStretched(std::to_string(score.result).c_str(),(Config::screenWidth + w + w_number) / 2.0f,currY,fontSize,BLACK);
        currY+=fontSize+spacing;
    }
}

ScreenType LeaderboardScreen::nextScreen() {
    ScreenType next = SCREEN_LEADERBOARD;
    if (action == Action::Exit) {
        next = SCREEN_START;
    } 

    action = Action::None; // Reset to prevent constant switching
    return next;
}
