#pragma once

#include <memory>

#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"

enum ScreenType {
    SCREEN_MENU,
    SCREEN_GAME,
    SCREEN_OPTIONS
};

class Screen {
public:
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    
    // Return nullptr to keep current screen, or a new screen to transition
    virtual std::unique_ptr<Screen> nextScreen() = 0;
    
    virtual ~Screen() = default;
};
    
