#include "Screen.h"

Screen::Screen(Renderer& r, MusicPlayer& m)
    : renderer(r), music(m) {}

bool Screen::wantsExit() const {
    return false;
}