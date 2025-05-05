#pragma once

#include "Screen.h"
#include <memory>

class Renderer;
class MusicPlayer;
class GameData;

class GameScreen : public Screen {
    GameData& game;

    float gameTime = 0;
    float physicsTime = 0;

    bool goToOptions = false;

public:
    GameScreen(Renderer& r, MusicPlayer& m, GameData& g);

    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
};
