#include "MenuScreen.h"
#include "GameScreen.h"

#include "../config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../utility/Button.h"
#include "../utility/Scaler.h"

#include <raylib.h>

MenuScreen::MenuScreen() {
    int w = 200, h = 60;
    playButton = createButton((screenWidth - w) / 2.0f, (screenHeight - h) / 2.0f, w, h, "PLAY");

    // Initialize shared resources
    renderer = std::make_unique<Renderer>(screenWidth, screenHeight);
    music = std::make_unique<MusicPlayer>();
    game = std::make_unique<GameData>();

    screenTarget = LoadRenderTexture(screenWidth, screenHeight);
    if (screenTarget.texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to create render texture for screen");
    }
}

void MenuScreen::update(float dt) {
    (void)dt; // Unused
    Vector2 mouse = getVirtualPosition(GetMousePosition());
    if (isButtonClicked(playButton, mouse)) {
        playClicked = true;
    }
}

void MenuScreen::draw() {
    BeginTextureMode(screenTarget);
        ClearBackground(GRAY);
        drawButton(playButton);
    EndTextureMode();

    BeginDrawing();
        ClearBackground(RAYWHITE);
        Rectangle source = { 0, 0, (float)screenTarget.texture.width, -(float)screenTarget.texture.height };
        Rectangle dest = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
        DrawTexturePro(screenTarget.texture, source, dest, {0, 0}, 0.0f, WHITE);
    EndDrawing();
}

std::unique_ptr<Screen> MenuScreen::nextScreen() {
    if (playClicked) {
        return std::make_unique<GameScreen>(
            std::move(renderer),
            std::move(music),
            std::move(game)
        );
    }
    return nullptr;
}
