#include "GameScreen.h"
#include "OptionsScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../UI/Scaler.h"

#include <sstream>
#include <iomanip>
#include <raylib.h>

GameScreen::GameScreen( GameData& g)
    : Screen(), game(g) {}

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

void GameScreen::draw() {}

void GameScreen::drawScore(){
    int score = game.getScore();
    int fontSize=50;
    int spacing = 10;
    //do something like if you want different font
    //Font customFont = LoadFontEx(fontFlie.c_str(), fontSize, 0, 0)
    Font customFont = GetFontDefault();
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(8) << score;
    std::string scoreText;
    ss >> scoreText;
    const char* text = scoreText.c_str();
    DrawTextStretched(text, Config::screenWidth / 2.0f, Config::screenHeight / 10.0f, fontSize, YELLOW);
}

ScreenType GameScreen::nextScreen() {
    if (goToOptions) {
        goToOptions = false;
        return SCREEN_OPTIONS;
    }
    return SCREEN_GAME;
}
