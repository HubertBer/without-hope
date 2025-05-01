#include "Screen.h"

Screen::Screen(std::unique_ptr<Renderer> r, std::unique_ptr<MusicPlayer> m)
    : renderer(std::move(r)), music(std::move(m)) {
    screenTarget = LoadRenderTexture(Config::screenWidth, Config::screenHeight);
    if (screenTarget.texture.id == 0) {
        TraceLog(LOG_ERROR, "Failed to create render texture for screen");
    }
}

bool Screen::wantsExit() const {
    return false;
}
