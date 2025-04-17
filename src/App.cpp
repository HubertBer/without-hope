#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>

#include "GameData.h"
#include "Renderer.h"
#include "ScreenManager.h"
#include "music/MusicPlayer.h"

#include "config.h"

#define GLSL_VERSION 330

int main() {
    // Make the window resizable
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "without-hope");
    SetTargetFPS(300);
    SetRandomSeed(0);

    SetExitKey(0); // Disable exit key (ESC) to allow for custom exit handling

    ScreenType currentScreen = SCREEN_MENU;

    std::unique_ptr<GameData> game = nullptr;
    std::unique_ptr<Renderer> renderer = nullptr;
    std::unique_ptr<MusicPlayer> musicPlayer = nullptr;

    float gameTime = 0;
    float physicsTime = 0;

    while (!WindowShouldClose()) {
        switch (currentScreen) {
            case SCREEN_MENU: {
                currentScreen = drawMenu();
                break;
            }

            case SCREEN_GAME: {
                // init the game if needed
                if (!game) {
                    game = std::make_unique<GameData>();
                    renderer = std::make_unique<Renderer>(screenWidth, screenHeight);
                    musicPlayer = std::make_unique<MusicPlayer>();
                }

                if (IsKeyPressed(KEY_ESCAPE)) {
                    currentScreen = SCREEN_OPTIONS;
                    continue;
                }

                // PHYSICS SIMULATION - CONSTANT FRAME TIME SIMULATION
                float dt = GetFrameTime();
                gameTime += dt;
                if(dt > 0.25f){
                    dt = 0.25f; // If the program lags, just slow it down
                }
                while(physicsTime < gameTime){
                    physicsTime += GameData::physicsDt;
                    game->physicsUpdate();
                }
                game->gameUpdate(dt);

                renderer->draw(*game);
                musicPlayer->play(*game);
                break;
            }

            case SCREEN_OPTIONS: {
                currentScreen = drawOptions();

                if (currentScreen == SCREEN_MENU) {
                    game.reset();
                    renderer.reset();
                    musicPlayer.reset();
                    gameTime = 0;
                    physicsTime = 0;
                }

                break;
            }

            default: {
                break;
            }
        }
    }

    CloseWindow();
    return 0;
}
