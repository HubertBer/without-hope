#include "OptionsScreen.h"
#include "GameScreen.h"
#include "StartScreen.h"

#include "../Config.h"
#include "../Renderer.h"
#include "../GameData.h"
#include "../music/MusicPlayer.h"
#include "../UI/Scaler.h"
#include "../WindowManager.h"

#include <raylib.h>

OptionsScreen::OptionsScreen(GameData& g,bool& musicOn)
    : Screen(), game(g),musicOn(musicOn) {
    int w = 200, h = 60, spacing = 20;
    float startY = (Config::screenHeight - (h * 4 + spacing * 3)) / 2.0f;

    resumeButton = createButton((Config::screenWidth - w) / 2.0f, startY, w, h, "RESUME");
    exitToMenuButton = createButton((Config::screenWidth - w) / 2.0f, startY + h + spacing, w, h, "MAIN MENU");
    musicOffButton = createButton((Config::screenWidth - w) / 2.0f, startY + 2*h + 2*spacing, w, h, "MUSIC: ON");
    musicOnButton = createButton((Config::screenWidth - w) / 2.0f, startY + 2*h + 2*spacing, w, h, "MUSIC: OFF");
    fullscreenToggleButton = createButton((Config::screenWidth - w) / 2.0f, startY + 3*h + 3*spacing, w, h, WindowManager::IsFullscreen() ? "WINDOWED" : "FULLSCREEN");
}

void OptionsScreen::update(float dt) {
    (void)dt;
    if (isButtonClicked(resumeButton)) action = Action::Resume;
    if (isButtonClicked(exitToMenuButton)) action = Action::Exit;
    if (isButtonClicked(musicOffButton)||isButtonClicked(musicOnButton)) musicOn=!musicOn;
    if (isButtonClicked(fullscreenToggleButton)) {
        WindowManager::ToggleFullscreen();
        fullscreenToggleButton.label = WindowManager::IsFullscreen() ? "WINDOWED" : "FULLSCREEN";
    }
}

void OptionsScreen::draw() {
    ClearBackground(GRAY);
    drawButton(resumeButton);
    drawButton(exitToMenuButton);
    if(musicOn){
        drawButton(musicOffButton);
    }else{
        drawButton(musicOnButton);
    }
    drawButton(fullscreenToggleButton);
}

ScreenType OptionsScreen::nextScreen() {
    ScreenType next = SCREEN_OPTIONS;

    if (action == Action::Resume) next = SCREEN_GAME;
    else if (action == Action::Exit) {
        next = SCREEN_START;
        game.endGame();
    } 

    action = Action::None; // Reset to prevent constant switching
    return next;
}
