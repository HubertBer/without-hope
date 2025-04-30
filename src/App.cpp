#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>

#include "GameData.h"
#include "Renderer.h"
#include "music/MusicPlayer.h"

#include "screens/Screen.h"
#include "screens/MenuScreen.h"

#include "Config.h"

#define GLSL_VERSION 330

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "without-hope");
    SetTargetFPS(300);
    SetRandomSeed(0);

    SetExitKey(0); // Disable exit key (ESC)

    std::unique_ptr<Screen> screen = std::make_unique<MenuScreen>();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        screen->update(dt);
        screen->draw();

        std::unique_ptr<Screen> next = screen->nextScreen();
        if (next) {
            screen = std::move(next);
        }
    }

    CloseWindow();
    return 0;
}