#pragma once

#include "Screen.h"
#include <memory>

class Renderer;
class MusicPlayer;
class GameData;

class GameScreen : public Screen {
    std::shared_ptr<std::unique_ptr<GameData>> game;

    float gameTime = 0;
    float physicsTime = 0;

    bool goToOptions = false;

public:
    GameScreen(std::shared_ptr<Renderer> r, std::shared_ptr<MusicPlayer> m, std::shared_ptr<std::unique_ptr<GameData>> g);

    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
};
