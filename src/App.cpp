#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>

#include "WindowManager.h"
#include "GameData.h"
#include "Renderer.h"
#include "music/MusicPlayer.h"

#include "screens/Screen.h"
#include "screens/MenuScreen.h"

#include "Config.h"

#define GLSL_VERSION 330

int main() {
    WindowManager::Init(screenWidth, screenHeight);
    SetRandomSeed(0);

    SetExitKey(0); // Disable exit key (ESC)

    std::unique_ptr<Screen> screen = std::make_unique<MenuScreen>(
        std::make_unique<Renderer>(screenWidth, screenHeight),
        std::make_unique<MusicPlayer>()
    );

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        screen->update(dt);
        screen->draw();

        std::unique_ptr<Screen> next = screen->nextScreen();
        if (next) {
            screen = std::move(next);
        }

        if (IsKeyPressed(KEY_F12)) {
            WindowManager::ToggleFullscreen();
        }
    }

    WindowManager::Shutdown();

    return 0;
}