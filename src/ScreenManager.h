#pragma once

#include <raylib.h>

#include "utility/Button.h"
#include "config.h"

enum ScreenType {
    SCREEN_MENU,
    SCREEN_GAME,
    SCREEN_OPTIONS
};

ScreenType drawMenu();
ScreenType drawOptions();