#pragma once
#include <raylib.h>

#include "Scaler.h"
#include "../Config.h"

#include <utility>
#include <string>
#include <iostream>

struct Button {
    Rectangle bounds;
    std::string label;
    int fontSize;
    Color bgColor;
    Color textColor;
};

inline Button createButton(float x, float y, float width, float height, const std::string& label, int fontSize = 30, Color bg = BLACK, Color fg = WHITE) {
    return Button{{x, y, width, height}, label, fontSize, bg, fg};
}

inline void drawButton(const Button& button) {
    Rectangle scaledBounds = getScaledRectangle(button.bounds);

    std::cerr << "Width: " << WindowManager::GetWidth() << ", Height: " << WindowManager::GetHeight() << std::endl;
    std::cerr << "Button bounds: " << button.bounds.x << ", " << button.bounds.y << ", " << button.bounds.width << ", " << button.bounds.height << std::endl;
    std::cerr << "Scaled bounds: " << scaledBounds.x << ", " << scaledBounds.y << ", " << scaledBounds.width << ", " << scaledBounds.height << std::endl;

    DrawRectangleRec(scaledBounds, button.bgColor);
    int textWidth = MeasureText(button.label.c_str(), button.fontSize);
    DrawText(
        button.label.c_str(),
        scaledBounds.x + (scaledBounds.width - textWidth) / 2,
        scaledBounds.y + (scaledBounds.height - button.fontSize) / 2,
        button.fontSize,
        button.textColor
    );
}

inline bool isButtonClicked(const Button& button) {
    Vector2 mouse = getVirtualPosition(GetMousePosition());
    return CheckCollisionPointRec(mouse, button.bounds) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
