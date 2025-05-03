#include "OptionsScreen.h"
#include "GameScreen.h"
#include "StartScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../UI/Scaler.h"

#include <raylib.h>

OptionsScreen::OptionsScreen(std::shared_ptr<Renderer> r, std::shared_ptr<MusicPlayer> m, std::shared_ptr<std::unique_ptr<GameData>> g)
    : Screen(std::move(r), std::move(m)), game(std::move(g)) {
    int w = 200, h = 60, spacing = 20;
    float startY = (Config::screenHeight - (h * 2 + spacing)) / 2.0f;

    resumeButton = createButton((Config::screenWidth - w) / 2.0f, startY, w, h, "RESUME");
    exitToMenuButton = createButton((Config::screenWidth - w) / 2.0f, startY + h + spacing, w, h, "MAIN MENU");
}

void OptionsScreen::update(float dt) {
    (void)dt;
    if (isButtonClicked(resumeButton)) action = Action::Resume;
    if (isButtonClicked(exitToMenuButton)) action = Action::Exit;
}

void OptionsScreen::draw() {
    BeginDrawing();
        ClearBackground(GRAY);
        drawButton(resumeButton);
        drawButton(exitToMenuButton);
    EndDrawing();
}

ScreenType OptionsScreen::nextScreen() {
    ScreenType next = SCREEN_OPTIONS;

    if (action == Action::Resume) next = SCREEN_GAME;
    else if (action == Action::Exit) {
        next = SCREEN_START;
        *game = std::make_unique<GameData>();
    } 

    action = Action::None; // Reset to prevent constant switching
    return next;
}
