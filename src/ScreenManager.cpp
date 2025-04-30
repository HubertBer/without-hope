#include "ScreenManager.h"

#include <raylib.h>
#include "utility/Button.h"
#include "config.h"

static RenderTexture2D screenTarget;

static void ensureScreenTarget() {
    if (screenTarget.texture.id == 0) {
        screenTarget = LoadRenderTexture(screenWidth, screenHeight);
        if (screenTarget.texture.id == 0) {
            TraceLog(LOG_ERROR, "Failed to create render texture for screen");
        }
    }
}

static void drawScreenToWindow() {
    BeginDrawing();
        ClearBackground(RAYWHITE);

        Rectangle source = { 0, 0, (float)screenTarget.texture.width, -(float)screenTarget.texture.height };
        Rectangle dest = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
        DrawTexturePro(screenTarget.texture, source, dest, {0, 0}, 0.0f, WHITE);
    EndDrawing();
}

ScreenType drawMenu() {
    ensureScreenTarget();

    int buttonWidth = 200;
    int buttonHeight = 60;

    Button playButton = createButton(
        (screenWidth - buttonWidth) / 2.0f,
        (screenHeight - buttonHeight) / 2.0f,
        buttonWidth,
        buttonHeight,
        "PLAY"
    );

    Vector2 mouse = GetMousePosition();
    bool clicked = isButtonClicked(playButton, mouse);

    BeginTextureMode(screenTarget);
        ClearBackground(GRAY);
        drawButton(playButton);
    EndTextureMode();

    drawScreenToWindow();
    return clicked ? SCREEN_GAME : SCREEN_MENU;
}

ScreenType drawOptions() {
    ensureScreenTarget();

    int buttonWidth = 200;
    int buttonHeight = 60;
    int spacing = 20;

    float startY = (screenHeight - (buttonHeight * 2 + spacing)) / 2.0f;

    Button resumeButton = createButton((screenWidth - buttonWidth) / 2.0f, startY, buttonWidth, buttonHeight, "RESUME");
    Button exitButton = createButton((screenWidth - buttonWidth) / 2.0f, startY + buttonHeight + spacing, buttonWidth, buttonHeight, "EXIT");

    Vector2 mouse = getVirtualPosition(GetMousePosition());
    if (isButtonClicked(resumeButton, mouse)) return SCREEN_GAME;
    if (isButtonClicked(exitButton, mouse)) return SCREEN_MENU;

    BeginTextureMode(screenTarget);
        ClearBackground(GRAY);

        const char* title = "PAUSED";
        int titleSize = 40;
        int titleWidth = MeasureText(title, titleSize);
        DrawText(title, screenWidth / 2 - titleWidth / 2, startY - 80, titleSize, BLACK);

        drawButton(resumeButton);
        drawButton(exitButton);
    EndTextureMode();

    drawScreenToWindow();
    return SCREEN_OPTIONS;
}
