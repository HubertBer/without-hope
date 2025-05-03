#include "Screen.h"

Screen::Screen(std::shared_ptr<Renderer> r, std::shared_ptr<MusicPlayer> m)
    : renderer(std::move(r)), music(std::move(m)) {}

bool Screen::wantsExit() const {
    return false;
}
