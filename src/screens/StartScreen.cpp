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

StartScreen::StartScreen(Renderer& r, MusicPlayer& m)
    : Screen(r, m) {
    int w = 200, h = 60;
    float startY = (Config::screenHeight - h) / 2.0f;

    playButton = createButton((Config::screenWidth - w) / 2.0f, startY, w, h, "PLAY");
    exitButton = createButton((Config::screenWidth - w) / 2.0f, startY + h + 20, w, h, "EXIT");
}

void StartScreen::update(float dt) {
    (void)dt; // Unused

    if (isButtonClicked(playButton)) {
        playClicked = true;
    }
    if (isButtonClicked(exitButton)) {
        exitClicked = true;
    }
}

void StartScreen::draw() {
    BeginDrawing();
        ClearBackground(GRAY);
        drawButton(playButton);
        drawButton(exitButton);
    EndDrawing();
}

ScreenType StartScreen::nextScreen() {
    if (playClicked) {
        playClicked = false;
        return SCREEN_GAME;
    }
    return SCREEN_START;
}

bool StartScreen::wantsExit() const {
    return exitClicked;
}
