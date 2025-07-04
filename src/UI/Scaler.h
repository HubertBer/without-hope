#pragma once

#include <utility>
#include <algorithm>
#include <iostream>

#include <raylib.h>

#include "../Config.h"
#include "../WindowManager.h"

inline std::pair<float, float> getScaling() {
    float w = WindowManager::IsFullscreen() ? (float)GetRenderWidth() : (float)GetScreenWidth();
    float h = WindowManager::IsFullscreen() ? (float)GetRenderHeight() : (float)GetScreenHeight();
    return { w / Config::screenWidth, h / Config::screenHeight };
}

inline Vector2 getVirtualPosition(Vector2 pos) {
    auto [scaleX, scaleY] = getScaling();
    return { pos.x / scaleX, pos.y / scaleY };
}

inline Rectangle getScaledRectangle(Rectangle rect) {
    auto [scaleX, scaleY] = getScaling();
    return { rect.x * scaleX, rect.y * scaleY, rect.width * scaleX, rect.height * scaleY };
}

inline void drawTextureStretched(RenderTexture2D texture) {
    Rectangle source = { 0, 0, (float)texture.texture.width, -(float)texture.texture.height };
    float destW = WindowManager::IsFullscreen() ? GetRenderWidth() : GetScreenWidth();
    float destH = WindowManager::IsFullscreen() ? GetRenderHeight() : GetScreenHeight();
    Rectangle dest = { 0, 0, destW, destH };

    DrawTexturePro(texture.texture, source, dest, { 0, 0 }, 0.0f, WHITE);
}

inline void DrawRectangleStretched(int posX, int posY, int width, int height, Color color) {
    Rectangle rect = { (float)posX, (float)posY, (float)width, (float)height };
    auto [scaleX, scaleY] = getScaling();
    Rectangle scaledRect = { rect.x * scaleX, rect.y * scaleY, rect.width * scaleX, rect.height * scaleY };
    DrawRectangleRec(scaledRect, color);
}

inline void DrawTextStretched(const char* text, int posX, int posY, int fontSize, Color color) {
    auto [sx, sy] = getScaling();
    float fx = posX * sx;
    float fy = posY * sy;
    float size = fontSize * sy;
    Font f = GetFontDefault();
    float spacing = 4.0f * sx;
    Vector2 ts = MeasureTextEx(f, text, size, spacing);
    DrawTextEx(f, text, { fx - ts.x * 0.5f, fy - size * 0.5f }, size, spacing, color);
}
