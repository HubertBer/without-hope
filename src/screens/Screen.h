#pragma once

#include <memory>
#include <raylib.h>

#include "../Renderer.h"
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
    Screen(std::shared_ptr<Renderer> r, std::shared_ptr<MusicPlayer> m);

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    // Return nullptr to keep current screen, or a new screen to transition
    virtual ScreenType nextScreen() = 0;

    virtual ~Screen() = default;

    virtual bool wantsExit() const;

protected:
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<MusicPlayer> music;
};
