#include "GameScreen.h"
#include "OptionsScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../UI/Scaler.h"

#include <raylib.h>

GameScreen::GameScreen(std::shared_ptr<Renderer> r, std::shared_ptr<MusicPlayer> m, std::shared_ptr<std::unique_ptr<GameData>> g)
    : Screen(std::move(r), std::move(m)), game(std::move(g)) {}

void GameScreen::update(float dt) {
    gameTime += dt;
    if (dt > 0.25f) {
        dt = 0.25f;
    }

    while(physicsTime < gameTime){
        physicsTime += GameData::physicsDt;
        (*game)->physicsUpdate();
    }
    (*game)->gameUpdate(dt, 1 - (physicsTime - gameTime) / GameData::physicsDt);

    if (IsKeyPressed(KEY_ESCAPE)) {
        goToOptions = true;
    }
}

void GameScreen::draw() {
    renderer->draw(**game);
    music->play(**game);
}

ScreenType GameScreen::nextScreen() {
    if (goToOptions) {
        goToOptions = false;
        return SCREEN_OPTIONS;
    }
    return SCREEN_GAME;
}
