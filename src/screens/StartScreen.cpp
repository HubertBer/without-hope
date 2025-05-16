#include "StartScreen.h"

#include "Screen.h"
#include "GameScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../WindowManager.h"
#include "../music/MusicPlayer.h"
#include "../UI/Button.h"
#include "../UI/Scaler.h"

#include <raylib.h>

constexpr int BUTTON_WIDTH = 200;
constexpr int BUTTON_HEIGHT = 60;
constexpr int BUTTON_SPACING = 20;
constexpr int TEXTBOX_WIDTH = 300;
constexpr int TEXTBOX_HEIGHT = 60;
constexpr int TEXTBOX_OFFSET_Y = 180;
constexpr int LABEL_FONT_SIZE = 40;

StartScreen::StartScreen(std::string* const name)
    : Screen(), name(name) {
    
    float centerX = Config::screenWidth / 2.0f;
    float startY = Config::screenHeight / 2.0f;

    playButton = createButton(centerX - BUTTON_WIDTH / 2.0f, startY, BUTTON_WIDTH, BUTTON_HEIGHT, "PLAY");
    exitButton = createButton(centerX - BUTTON_WIDTH / 2.0f, startY + BUTTON_HEIGHT + BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT, "EXIT");
    leaderboardButton = createButton(centerX - BUTTON_WIDTH / 2.0f, startY + 2 * (BUTTON_HEIGHT + BUTTON_SPACING), BUTTON_WIDTH, BUTTON_HEIGHT, "LEADERBOARD");
}

void StartScreen::update(float dt) {
    (void)dt; // Unused

    if (isButtonClicked(playButton)) {
        playClicked = true;
    }
    if (isButtonClicked(exitButton)) {
        exitClicked = true;
    }
    if (isButtonClicked(leaderboardButton)) {
        leaderboardClicked = true;
    }
    //code stolen from https://www.raylib.com/examples/text/loader.html?name=text_input_box
    //and changed for strings
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0){
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)){
            name->push_back((char)key); // Add null terminator at the end of the string.
            letterCount++;
        }
        key = GetCharPressed();  // Check next character in the queue
    }
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (letterCount > 0){
            letterCount--;
            name->pop_back();
        }
    }

}

void StartScreen::draw() {
    ClearBackground(GRAY);

    drawButton(playButton);
    drawButton(exitButton);
    drawButton(leaderboardButton);

    drawCodenameBox();
}

void StartScreen::drawCodenameBox() const {
    float centerX = Config::screenWidth / 2.0f;
    float labelY = Config::screenHeight / 2.0f - TEXTBOX_OFFSET_Y - 80;
    float boxY = Config::screenHeight / 2.0f - TEXTBOX_OFFSET_Y;

    DrawTextStretched("YOUR CODENAME:", centerX, labelY, LABEL_FONT_SIZE, BLACK);
    DrawRectangleStretched(centerX - TEXTBOX_WIDTH / 2.0f , boxY - 30, TEXTBOX_WIDTH, TEXTBOX_HEIGHT, DARKBLUE);
    DrawTextStretched(name->c_str(), centerX, boxY, LABEL_FONT_SIZE, SKYBLUE);
}


ScreenType StartScreen::nextScreen() {
    if (playClicked) {
        playClicked = false;
        std::cout<<*name<<'\n';
        return SCREEN_GAME;
    }
    if(leaderboardClicked){
        leaderboardClicked = false;
        return SCREEN_LEADERBOARD;
    }
    return SCREEN_START;
}

bool StartScreen::wantsExit() const {
    return exitClicked;
}
