#pragma once
#include <raylib.h>
#include <string>

struct InputField {
    Rectangle bounds;
    std::string input;
    int fontSize;
    Color bgColor;
    Color textColor;
};

inline InputField createInputField(float x, float y, float width, float height, std::string& input, int fontSize = 30, Color bg = BLACK, Color fg = WHITE) {
    return InputField{{x, y, width, height}, input, fontSize, bg, fg};
}

inline void drawInputField(const InputField& inputField) {
    DrawRectangleRec(inputField.bounds, inputField.bgColor);
    int textWidth = MeasureText(inputField.label.c_str(), inputField.fontSize);
    DrawText(
        inputField.label.c_str(),
        inputField.bounds.x + (inputField.bounds.width - textWidth) / 2,
        inputField.bounds.y + (inputField.bounds.height - inputField.fontSize) / 2,
        inputField.fontSize,
        inputField.textColor
    );
}
