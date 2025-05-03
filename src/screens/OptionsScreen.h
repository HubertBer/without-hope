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

    std::shared_ptr<std::unique_ptr<GameData>> game;

    enum class Action {
        None,
        Resume,
        Exit
    };

    Action action = Action::None;

public:
    OptionsScreen(std::shared_ptr<Renderer> r, std::shared_ptr<MusicPlayer> m, std::shared_ptr<std::unique_ptr<GameData>> g);

    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
};
