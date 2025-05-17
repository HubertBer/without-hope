#pragma once

#include "Screen.h"
#include <memory>
#include <string>
class MusicPlayer;
class GameData;

class GameScreen : public Screen {
public:
    GameScreen(GameData& g);
    void update(float dt) override;
    void draw() override;
    void drawScore();
    ScreenType nextScreen() override;
    GameData& game;
private:
    float gameTime = 0;
    float physicsTime = 0;
    bool goToOptions = false;
    inline static const std::string fontFlie = "../resources/fonts/digital-7.regular.ttf";
};
