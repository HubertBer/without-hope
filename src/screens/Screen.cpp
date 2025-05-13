#include "Screen.h"

Screen::Screen(MusicPlayer& m)
    : music(m) {}

bool Screen::wantsExit() const {
    return false;
}