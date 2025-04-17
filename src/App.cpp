#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>
#include <map>

#include "WindowManager.h"
#include "GameData.h"
#include "Renderer.h"
#include "ScreenManager.h"
#include "music/MusicPlayer.h"

#include "screens/Screen.h"
#include "screens/StartScreen.h"
#include "screens/GameScreen.h"
#include "screens/OptionsScreen.h"

#include "Config.h"

#define GLSL_VERSION 330

int main() {
    WindowManager::Init(Config::screenWidth, Config::screenHeight);
    SetRandomSeed(0);

    SetExitKey(0); // Disable exit key (ESC)

    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(Config::screenWidth, Config::screenHeight);
    std::shared_ptr<MusicPlayer> music = std::make_shared<MusicPlayer>();
    std::shared_ptr<std::unique_ptr<GameData>> gameData = std::make_shared<std::unique_ptr<GameData>>(std::make_unique<GameData>());

    std::map<ScreenType, std::unique_ptr<Screen>> screens;
    screens[SCREEN_START] = std::make_unique<StartScreen>(renderer, music);
    screens[SCREEN_GAME] = std::make_unique<GameScreen>(renderer, music, gameData);
    screens[SCREEN_OPTIONS] = std::make_unique<OptionsScreen>(renderer, music, gameData);

    ScreenType currentScreen = SCREEN_START;

    while (!WindowShouldClose() && !screens[currentScreen]->wantsExit()) {
        float dt = GetFrameTime();

        screens[currentScreen]->update(dt);
        screens[currentScreen]->draw();
       currentScreen = screens[currentScreen]->nextScreen();
       
        if (IsKeyPressed(KEY_F10)) {
            WindowManager::ToggleFullscreen();
        }
    }

    WindowManager::Shutdown();

    return 0;
}