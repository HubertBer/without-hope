#pragma once

#include "Screen.h"

#include "../UI/Button.h"

#include <raylib.h>

#include <memory>

class MusicPlayer;
class GameData;

class StartScreen : public Screen {
    Button playButton, exitButton,leaderboardButton;
    bool playClicked = false;
    bool exitClicked = false;
    bool leaderboardClicked = false;
    static constexpr int MAX_INPUT_CHARS = 9;
    std::string* const  name;
    int letterCount=0;

public:
    StartScreen(MusicPlayer& m,std::string* const name);
    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
    bool wantsExit() const override;
    void drawCodenameBox() const;
};
