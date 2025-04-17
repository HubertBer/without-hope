#pragma once

#include <utility>
#include <algorithm>

#include <raylib.h>

#include "../config.h"

inline std::pair<float, float> getScaling() {
    float scaleX = static_cast<float>(GetScreenWidth()) / screenWidth;
    float scaleY = static_cast<float>(GetScreenHeight()) / screenHeight;
    return {scaleX, scaleY};
}

// Rectangles
inline void drawRectangleRecScaled(Rectangle rec, Color color) {
    auto [scaleX, scaleY] = getScaling();
    Rectangle scaledRec = {rec.x * scaleX, rec.y * scaleY, rec.width * scaleX, rec.height * scaleY};
    DrawRectangleRec(scaledRec, color);
}

// Text

inline void drawTextScaled(const char* text, float x, float y, int fontSize, Color color) {
    auto [scaleX, scaleY] = getScaling();
    Vector2 scaledPos = {x * scaleX, y * scaleY};
    int scaledFontSize = static_cast<int>(fontSize * std::min(scaleX, scaleY));
    DrawText(text, static_cast<int>(scaledPos.x), static_cast<int>(scaledPos.y), scaledFontSize, color);
}