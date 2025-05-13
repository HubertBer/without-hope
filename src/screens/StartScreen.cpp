#include "StartScreen.h"

#include "Screen.h"
#include "GameScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../WindowManager.h"
#include "../music/MusicPlayer.h"
#include "../UI/Button.h"
#include "../UI/Scaler.h"

#include <raylib.h>

StartScreen::StartScreen(MusicPlayer& m)
    : Screen(m) {
    int w = 200, h = 60;
    float startY = (Config::screenHeight - h) / 2.0f;

    playButton = createButton((Config::screenWidth - w) / 2.0f, startY, w, h, "PLAY");
    exitButton = createButton((Config::screenWidth - w) / 2.0f, startY + h + 20, w, h, "EXIT");
    leaderboardButton = createButton((Config::screenWidth - w) / 2.0f, startY + 2*h + 2*20, w, h, "LEADERBOARD");
}

void StartScreen::update(float dt) {
    (void)dt; // Unused

    if (isButtonClicked(playButton)) {
        playClicked = true;
    }
    if (isButtonClicked(exitButton)) {
        exitClicked = true;
    }
    if (isButtonClicked(leaderboardButton)) {
        leaderboardClicked = true;
    }
}

void StartScreen::draw() {
    ClearBackground(GRAY);
    drawButton(playButton);
    drawButton(exitButton);
    drawButton(leaderboardButton);
}

ScreenType StartScreen::nextScreen() {
    if (playClicked) {
        playClicked = false;
        return SCREEN_GAME;
    }
    if(leaderboardClicked){
        leaderboardClicked = false;
        return SCREEN_LEADERBOARD;
    }
    return SCREEN_START;
}

bool StartScreen::wantsExit() const {
    return exitClicked;
}
