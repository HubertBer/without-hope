#pragma once

#include "Screen.h"

#include "../UI/Button.h"

#include <raylib.h>

#include <memory>

class MusicPlayer;
class GameData;

class OptionsScreen : public Screen {
    Button resumeButton, exitToMenuButton, musicOnButton,musicOffButton, fullscreenToggleButton;

    GameData& game;
    bool& musicOn;

    enum class Action {
        None,
        Resume,
        Exit
    };

    Action action = Action::None;

public:
    OptionsScreen(GameData& g,bool& musicOn);

    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
};
