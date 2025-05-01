#include "WindowManager.h"

#include "Config.h"

#include <raylib.h>

#include <iostream>

int WindowManager::screenWidth = Config::screenWidth;
int WindowManager::screenHeight = Config::screenHeight;
bool WindowManager::isFullscreen = false;

void WindowManager::Init(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "without-hope");
    SetTargetFPS(300);
}

void WindowManager::Shutdown() {
    CloseWindow();
}

void WindowManager::ToggleFullscreen() {
    if (!isFullscreen) {
        ::ToggleFullscreen();
        isFullscreen = true;
    } else {
        ::ToggleFullscreen();
        isFullscreen = false;
    }
}

void WindowManager::SetResolution(int width, int height) {
    if (!isFullscreen) {
        SetWindowSize(width, height);
        screenWidth = width;
        screenHeight = height;
    }
}

bool WindowManager::IsFullscreen() {
    return isFullscreen;
}

int WindowManager::GetWidth() {
    return screenWidth;
}

int WindowManager::GetHeight() {
    return screenHeight;
}
