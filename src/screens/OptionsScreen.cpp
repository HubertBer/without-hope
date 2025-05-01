#include "OptionsScreen.h"
#include "GameScreen.h"
#include "MenuScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../utility/Scaler.h"

#include <raylib.h>

OptionsScreen::OptionsScreen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m, std::unique_ptr<GameData> g)
    : Screen(std::move(r), std::move(m)), game(std::move(g)) {
    int w = 200, h = 60, spacing = 20;
    float startY = (screenHeight - (h * 2 + spacing)) / 2.0f;

    resumeButton = createButton((screenWidth - w) / 2.0f, startY, w, h, "RESUME");
    exitButton = createButton((screenWidth - w) / 2.0f, startY + h + spacing, w, h, "EXIT");
}

void OptionsScreen::update(float dt) {
    (void)dt;
    if (isButtonClicked(resumeButton)) action = RESUME;
    if (isButtonClicked(exitButton)) action = EXIT;
}

void OptionsScreen::draw() {
    BeginTextureMode(screenTarget);
        ClearBackground(GRAY);
        const char* title = "PAUSED";
        int titleSize = 40;
        int titleWidth = MeasureText(title, titleSize);
        DrawText(title, screenWidth / 2 - titleWidth / 2, resumeButton.bounds.y - 80, titleSize, BLACK);

        drawButton(resumeButton);
        drawButton(exitButton);
    EndTextureMode();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        drawTextureStretched(screenTarget);
    EndDrawing();
}

std::unique_ptr<Screen> OptionsScreen::nextScreen() {
    if (action == RESUME) {
        return std::make_unique<GameScreen>(
            std::move(renderer), std::move(music), std::move(game)
        );
    } 
    else if (action == EXIT) {
        return std::make_unique<MenuScreen>(
            std::move(renderer), std::move(music)
        );
    }
    return nullptr;
}
