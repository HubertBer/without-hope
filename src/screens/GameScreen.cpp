#include "GameScreen.h"
#include "OptionsScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../UI/Scaler.h"

#include <raylib.h>

GameScreen::GameScreen(MusicPlayer& m, GameData& g)
    : Screen(m), game(g) {}

void GameScreen::update(float dt) {
    gameTime += dt;
    if (dt > 0.25f) {
        dt = 0.25f;
    }

    while(physicsTime < gameTime){
        physicsTime += GameData::physicsDt;
        game.physicsUpdate();
    }
    bool gameNeedsReset = game.gameUpdate(dt, 
                            1 - (physicsTime - gameTime) / GameData::physicsDt);
    if (gameNeedsReset) GameData::reset(game);

    if (IsKeyPressed(KEY_ESCAPE)) {
        goToOptions = true;
    }
}

void GameScreen::draw() {
    music.play(game);
}

void GameScreen::drawScore(){
    int score = game.getScore();
    const char* text =std::to_string(score).c_str();  
    int textWidth = MeasureText(text, 50);
    DrawText(text ,(Config::screenWidth-textWidth)/2,Config::screenHeight/10,50,YELLOW);
}

ScreenType GameScreen::nextScreen() {
    if (goToOptions) {
        goToOptions = false;
        return SCREEN_OPTIONS;
    }
    return SCREEN_GAME;
}
