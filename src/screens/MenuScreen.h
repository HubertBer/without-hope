#pragma once

#include "Screen.h"

#include "../utility/Button.h"

#include <raylib.h>

#include <memory>

class Renderer;
class MusicPlayer;
class GameData;

class MenuScreen : public Screen {
    Button playButton;
    bool playClicked = false;

    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<MusicPlayer> music;
    std::unique_ptr<GameData> game;

    RenderTexture2D screenTarget;

public:
    MenuScreen();

    void update(float dt) override;
    void draw() override;
    std::unique_ptr<Screen> nextScreen() override;
};
