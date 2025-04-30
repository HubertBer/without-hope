#pragma once

#include <utility>
#include <algorithm>

#include <raylib.h>

#include "../Config.h"

inline std::pair<float, float> getScaling() {
    float scaleX = static_cast<float>(GetScreenWidth()) / screenWidth;
    float scaleY = static_cast<float>(GetScreenHeight()) / screenHeight;
    return {scaleX, scaleY};
}

inline Vector2 getVirtualPosition(Vector2 pos) {
    auto [scaleX, scaleY] = getScaling();
    return {pos.x / scaleX, pos.y / scaleY};
}