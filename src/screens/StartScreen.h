#pragma once

#include "Screen.h"

#include "../UI/Button.h"

#include <raylib.h>

#include <memory>

class Renderer;
class MusicPlayer;
class GameData;

class StartScreen : public Screen {
    Button playButton, exitButton;
    bool playClicked = false;
    bool exitClicked = false;

public:
    StartScreen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m);
    void update(float dt) override;
    void draw() override;
    std::unique_ptr<Screen> nextScreen() override;
    bool wantsExit() const override;
};
