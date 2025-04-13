#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>

#include "GameData.h"
#include "Renderer.h"

const int screenWidth = 1280;
const int screenHeight = 720;

#define GLSL_VERSION 330

int main() {
    InitWindow(screenWidth, screenHeight, "without-hope");
    SetTargetFPS(300);
    SetRandomSeed(0);

    // Initialization happening in GameData constructor
    GameData game;
    Renderer renderer(screenWidth, screenHeight);

    float gameTime = 0;
    float physicsTime = 0;

    while (!WindowShouldClose()) {
        // PHYSICS SIMULATION - CONSTANT FRAME TIME SIMULATION
        float dt = GetFrameTime();
        gameTime += dt;
        if(dt > 0.25f){
            dt = 0.25f; // If the program lags, just slow it down
        }
        while(physicsTime < gameTime){
            physicsTime += GameData::physicsDt;
            game.physicsUpdate();
        }
        game.gameUpdate(dt);

        renderer.draw(game);
    }

    CloseWindow();
    return 0;
}
