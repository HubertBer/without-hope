#include "ScreenManager.h"

#include "utility/Button.h"
#include "config.h"

ScreenType drawMenu() {
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

    BeginDrawing();
        ClearBackground(GRAY);
        drawButton(playButton);
    EndDrawing();

    return clicked ? SCREEN_GAME : SCREEN_MENU;
}

ScreenType drawOptions() {
    int buttonWidth = 200;
    int buttonHeight = 60;
    int spacing = 20;

    float startY = (screenHeight - (buttonHeight * 2 + spacing)) / 2.0f;
    Button resumeButton = createButton((screenWidth - buttonWidth) / 2.0f, startY, buttonWidth, buttonHeight, "RESUME");
    Button exitButton = createButton((screenWidth - buttonWidth) / 2.0f, startY + buttonHeight + spacing, buttonWidth, buttonHeight, "EXIT");

    Vector2 mouse = GetMousePosition();

    if (isButtonClicked(resumeButton, mouse)) return SCREEN_GAME;
    if (isButtonClicked(exitButton, mouse)) return SCREEN_MENU;

    BeginDrawing();
        ClearBackground(GRAY);

        const char* title = "PAUSED";
        int titleSize = 40;
        int titleWidth = MeasureText(title, titleSize);
        drawTextScaled(title, screenWidth / 2 - titleWidth / 2, startY - 80, titleSize, BLACK);

        drawButton(resumeButton);
        drawButton(exitButton);
    EndDrawing();

    return SCREEN_OPTIONS;
}

