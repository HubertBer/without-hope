#pragma once

#include "Screen.h"

#include "../UI/Button.h"

#include <raylib.h>

#include <memory>

class MusicPlayer;
class GameData;

class StartScreen : public Screen {
    Button playButton, exitButton;
    bool playClicked = false;
    bool exitClicked = false;

public:
    StartScreen(MusicPlayer& m);
    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
    bool wantsExit() const override;
};
