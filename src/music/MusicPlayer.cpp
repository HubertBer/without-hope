#include "MusicPlayer.h"
#include "../screens/Screen.h"

MusicPlayer::MusicPlayer(bool& musicOn):musicOn(musicOn){
    InitAudioDevice();
    baseMusic = LoadMusicStream("resources/music/without-hope-base.wav");
    melody = {LoadMusicStream("resources/music/melody2.wav"),0};


    PlayMusicStream(baseMusic);
    SetMusicVolume(baseMusic,baseMusic.volume);
    PlayMusicStream(melody);
    SetMusicVolume(melody,melody.volume);

}

void MusicPlayer::play(ScreenType currentScreenType){

    if(currentScreenType == SCREEN_GAME){
        melody.volume = std::min(1.0f,melody.volume+fadeawaySpeed);
    }else{
        melody.volume = std::max(0.0f,melody.volume-fadeawaySpeed);
    }

    UpdateMusicStream(baseMusic);
    UpdateMusicStream(melody);
    SetMusicVolume(melody,melody.volume*musicOn);
    SetMusicVolume(baseMusic,baseMusic.volume*musicOn);
    

}

MusicPlayer::~MusicPlayer() {
    UnloadMusicStream(baseMusic);
    UnloadMusicStream(melody);
    CloseAudioDevice();
}