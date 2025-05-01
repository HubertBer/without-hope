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

    std::unique_ptr<GameData> game;

    enum { NONE, RESUME, EXIT } action = NONE;

public:
    OptionsScreen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m, std::unique_ptr<GameData> g);

    void update(float dt) override;
    void draw() override;
    std::unique_ptr<Screen> nextScreen() override;
};
