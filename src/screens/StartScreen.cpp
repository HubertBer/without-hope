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

StartScreen::StartScreen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m)
    : Screen(std::move(r), std::move(m)) {
    int w = 200, h = 60;
    float startY = (screenHeight - h) / 2.0f;

    playButton = createButton((screenWidth - w) / 2.0f, startY, w, h, "PLAY");
    exitButton = createButton((screenWidth - w) / 2.0f, startY + h + 20, w, h, "EXIT");
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
    BeginTextureMode(screenTarget);
        ClearBackground(GRAY);
        drawButton(playButton);
        drawButton(exitButton);
    EndTextureMode();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        drawTextureStretched(screenTarget);
    EndDrawing();
}

std::unique_ptr<Screen> StartScreen::nextScreen() {
    if (playClicked) {
        return std::make_unique<GameScreen>(
            std::move(renderer),
            std::move(music),
            std::make_unique<GameData>()
        );
    }
    return nullptr;
}

bool StartScreen::wantsExit() const {
    return exitClicked;
}
