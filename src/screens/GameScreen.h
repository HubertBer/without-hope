#pragma once

#include "Screen.h"
#include <memory>

class MusicPlayer;
class GameData;

class GameScreen : public Screen {
public:
    GameScreen(MusicPlayer& m, GameData& g);
    
    void update(float dt) override;
    void draw() override;
    ScreenType nextScreen() override;
    GameData& game;
private:
    float gameTime = 0;
    float physicsTime = 0;
    bool goToOptions = false;
};
