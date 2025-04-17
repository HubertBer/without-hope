#pragma once
#include <raylib.h>

#include "Scaler.h"
#include "config.h"
#include <utility>

struct Button {
    Rectangle bounds;
    const char* label;
    int fontSize;
    Color bgColor;
    Color textColor;
};

inline Button createButton(float x, float y, float width, float height, const char* label, int fontSize = 30, Color bg = BLACK, Color fg = WHITE) {
    return Button{{x, y, width, height}, label, fontSize, bg, fg};
}

inline void drawButton(const Button& button) {
    drawRectangleRecScaled(button.bounds, button.bgColor);
    int textWidth = MeasureText(button.label, button.fontSize);
    drawTextScaled(
        button.label,
        button.bounds.x + (button.bounds.width - textWidth) / 2,
        button.bounds.y + (button.bounds.height - button.fontSize) / 2,
        button.fontSize,
        button.textColor
    );
}

inline bool isButtonClicked(const Button& button, Vector2 mouse) {
    auto [scaleX, scaleY] = getScaling();
    mouse.x /= scaleX;
    mouse.y /= scaleY;
    return CheckCollisionPointRec(mouse, button.bounds) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
