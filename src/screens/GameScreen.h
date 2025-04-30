#pragma once

#include "Screen.h"
#include <memory>

class Renderer;
class MusicPlayer;
class GameData;

class GameScreen : public Screen {
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<MusicPlayer> music;
    std::unique_ptr<GameData> game;

    float gameTime = 0;
    float physicsTime = 0;

    bool goToOptions = false;

public:
    GameScreen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m, std::unique_ptr<GameData> g);

    void update(float dt) override;
    void draw() override;
    std::unique_ptr<Screen> nextScreen() override;
};
