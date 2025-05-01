#include "MenuScreen.h"

#include "Screen.h"
#include "GameScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../utility/Button.h"
#include "../utility/Scaler.h"

#include <raylib.h>

MenuScreen::MenuScreen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m)
    : Screen(std::move(r), std::move(m)) {
    int w = 200, h = 60;
    float startY = (screenHeight - h) / 2.0f;

    playButton = createButton((screenWidth - w) / 2.0f, startY, w, h, "PLAY");
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
            std::make_unique<GameData>()
        );
    }
    return nullptr;
}
