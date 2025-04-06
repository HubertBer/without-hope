#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <memory>

#include "GameData.h"
#include "entities/Player.h"
#include "entities/SimpleEnemy.h"
#include "entities/SimpleBullet.h"

const int screenWidth = 1280;
const int screenHeight = 720;

int main() {
    InitWindow(screenWidth, screenHeight, "without-hope");
    SetTargetFPS(300);
    SetRandomSeed(0);

    // Initialization happening in GameData constructor
    GameData game;

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

        // DRAWING 
        BeginDrawing();
        ClearBackground(BLUE);
        game.draw(1 - (physicsTime - gameTime)/GameData::physicsDt);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
