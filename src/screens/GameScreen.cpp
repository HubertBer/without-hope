#include "GameScreen.h"
#include "OptionsScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../UI/Scaler.h"

#include <raylib.h>

GameScreen::GameScreen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m, std::unique_ptr<GameData> g)
    : Screen(std::move(r), std::move(m)), game(std::move(g)) {}

void GameScreen::update(float dt) {
    gameTime += dt;
    if (dt > 0.25f) {
        dt = 0.25f;
    }

    while(physicsTime < gameTime){
        physicsTime += GameData::physicsDt;
        game->physicsUpdate();
    }
    game->gameUpdate(dt, 1 - (physicsTime - gameTime) / GameData::physicsDt);

    if (IsKeyPressed(KEY_ESCAPE)) {
        goToOptions = true;
    }
}

void GameScreen::draw() {
    renderer->draw(*game, screenTarget);
    music->play(*game);
}

std::unique_ptr<Screen> GameScreen::nextScreen() {
    if (goToOptions) {
        return std::make_unique<OptionsScreen>(
            std::move(renderer),
            std::move(music),
            std::move(game)
        );
    }
    return nullptr;
}
