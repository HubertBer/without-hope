#pragma once

class WindowManager {
public:
    static void Init(int width, int height);
    static void Shutdown();

    static void ToggleFullscreen();
    static void SetResolution(int width, int height);

    static bool IsFullscreen();
    static int GetWidth();
    static int GetHeight();

private:
    static int screenWidth;
    static int screenHeight;
    static bool isFullscreen;
};
