#pragma once

#include <utility>
#include <algorithm>

#include <raylib.h>

#include "../Config.h"
#include "../WindowManager.h"

inline std::pair<float, float> getScaling() {
    float w = WindowManager::IsFullscreen() ? (float)GetRenderWidth() : (float)GetScreenWidth();
    float h = WindowManager::IsFullscreen() ? (float)GetRenderHeight() : (float)GetScreenHeight();
    return { w / screenWidth, h / screenHeight };
}

inline Vector2 getVirtualPosition(Vector2 pos) {
    auto [scaleX, scaleY] = getScaling();
    return { pos.x / scaleX, pos.y / scaleY };
}

inline void drawTextureStretched(RenderTexture2D texture) {
    Rectangle source = { 0, 0, (float)texture.texture.width, -(float)texture.texture.height };
    float destW = WindowManager::IsFullscreen() ? GetRenderWidth() : GetScreenWidth();
    float destH = WindowManager::IsFullscreen() ? GetRenderHeight() : GetScreenHeight();
    Rectangle dest = { 0, 0, destW, destH };

    DrawTexturePro(texture.texture, source, dest, { 0, 0 }, 0.0f, WHITE);
}