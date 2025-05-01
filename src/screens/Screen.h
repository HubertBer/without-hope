#pragma once

#include <memory>

#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../Config.h"

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

    Screen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m) : renderer(std::move(r)), music(std::move(m)) {
        screenTarget = LoadRenderTexture(screenWidth, screenHeight);
        if (screenTarget.texture.id == 0) {
            TraceLog(LOG_ERROR, "Failed to create render texture for screen");
        }
    }

protected:
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<MusicPlayer> music;

    RenderTexture2D screenTarget;
};
    
