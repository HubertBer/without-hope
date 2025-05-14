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

StartScreen::StartScreen(MusicPlayer& m,std::string* const name)
    : Screen(m),name(name) {
    int w = 200, h = 60;
    float startY = Config::screenHeight/2.0f;

    playButton = createButton((Config::screenWidth - w) / 2.0f, startY, w, h, "PLAY");
    exitButton = createButton((Config::screenWidth - w) / 2.0f, startY + h + 20, w, h, "EXIT");
    leaderboardButton = createButton((Config::screenWidth - w) / 2.0f, startY + 2*h + 2*20, w, h, "LEADERBOARD");
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
    DrawText("YOUR CODENAME:", (Config::screenWidth - 350) / 2.0f, Config::screenHeight/2.0f - 180-80, 40, BLACK);
    DrawRectangle( (Config::screenWidth-200)/2.0f-25, Config::screenHeight/2.0f - 180-10, 250, 60 ,DARKBLUE);
    DrawText(name->c_str(), (Config::screenWidth - 200) / 2.0f, Config::screenHeight/2.0f - 180, 40, SKYBLUE);
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
