#include "GameScreen.h"
#include "OptionsScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../UI/Scaler.h"

#include <raylib.h>

GameScreen::GameScreen(Renderer& r, MusicPlayer& m, GameData& g)
    : Screen(r, m), game(g) {}

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
    renderer.draw(game);
    music.play(game);
}

ScreenType GameScreen::nextScreen() {
    if (goToOptions) {
        goToOptions = false;
        return SCREEN_OPTIONS;
    }
    return SCREEN_GAME;
}
