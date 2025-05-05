#pragma once

#include <memory>
#include <raylib.h>

#include "../GameData.h"
#include "../WindowManager.h"
#include "../music/MusicPlayer.h"
#include "../Config.h"

enum ScreenType {
    SCREEN_START,
    SCREEN_GAME,
    SCREEN_OPTIONS
};

class Screen {
public:
    Screen(MusicPlayer& m);

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    // Return nullptr to keep current screen, or a new screen to transition
    virtual ScreenType nextScreen() = 0;

    // Screens could have allocated resources, which copy could cost
    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;

    virtual ~Screen() = default;

    virtual bool wantsExit() const;

protected:
    MusicPlayer& music;
};
