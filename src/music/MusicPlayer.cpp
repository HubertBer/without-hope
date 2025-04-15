#include "MusicPlayer.h"



MusicPlayer::MusicPlayer(){
    InitAudioDevice();
    
    //add music type for entities types here
    entityMusic[PLAYER] = LoadMusicStream("src/resources/music/piano.wav");
    entityMusic[SIMPLE_ENEMY] = LoadMusicStream("src/resources/music/simple-enemy.wav");


    for(auto& [type,music]:entityMusic){
        PlayMusicStream(music);
        SetMusicVolume(music,music.volume);
    }

}

void MusicPlayer::play(GameData& gameData){
    for(auto& [type,music]:entityMusic){

        UpdateMusicStream(music);

        if (gameData.checkPresent(type)) {
            music.volume=1.0f;
        } else {
            music.volume=std::max(0.0f,music.volume-fadeawaySpeed);
        }
        SetMusicVolume(music, music.volume);
    }
    
}

MusicPlayer::~MusicPlayer(){
    for(auto& [type,music]:entityMusic){
        UnloadMusicStream(music);
    }
    CloseAudioDevice();
}