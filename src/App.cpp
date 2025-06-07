#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>
#include <map>

#include "WindowManager.h"
#include "GameData.h"
#include "Renderer.h"
#include "music/MusicPlayer.h"

#include "screens/Screen.h"
#include "screens/StartScreen.h"
#include "screens/GameScreen.h"
#include "screens/OptionsScreen.h"
#include "screens/LeaderboardScreen.h"

#include "Config.h"

#define GLSL_VERSION 330

int main() {
    WindowManager::Init(Config::screenWidth, Config::screenHeight);
    SetRandomSeed(0);

    SetExitKey(0); // Disable exit key (ESC)

    std::string name;
    bool musicOn = true;
    Renderer::init(Config::screenWidth, Config::screenHeight);
    MusicPlayer music{musicOn};
    GameData gameData{&name};

    std::map<ScreenType, std::shared_ptr<Screen>> screens;
    screens[SCREEN_START] = std::make_shared<StartScreen>(gameData,&name);
    screens[SCREEN_GAME] = std::make_shared<GameScreen>(gameData);
    screens[SCREEN_OPTIONS] = std::make_shared<OptionsScreen>(gameData,musicOn);
    screens[SCREEN_LEADERBOARD] = std::make_shared<LeaderboardScreen>(gameData);
    
    ScreenType currentScreen = SCREEN_START;

    while (!WindowShouldClose() && !screens[currentScreen]->wantsExit()) {
        float dt = GetFrameTime();

        screens[currentScreen]->update(dt);
        Renderer::draw(screens[currentScreen], currentScreen);
        music.play(currentScreen);
        currentScreen = screens[currentScreen]->nextScreen();
    }

    WindowManager::Shutdown();

    return 0;
}