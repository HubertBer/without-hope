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

public:
    MenuScreen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m);
    void update(float dt) override;
    void draw() override;
    std::unique_ptr<Screen> nextScreen() override;
};
