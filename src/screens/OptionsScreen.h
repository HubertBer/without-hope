#pragma once

#include "Screen.h"

#include "../UI/Button.h"

#include <raylib.h>

#include <memory>

class Renderer;
class MusicPlayer;
class GameData;

class OptionsScreen : public Screen {
    Button resumeButton, exitToMenuButton;

    GameData& game;

    enum class Action {
        None,
        Resume,
        Exit
    };

    Action action = Action::None;

public:
    OptionsScreen(Renderer& r, MusicPlayer& m, GameData& g);

    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
};
