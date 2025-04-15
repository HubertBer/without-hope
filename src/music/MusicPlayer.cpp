#include "MusicPlayer.h"



MusicPlayer::MusicPlayer(){
    InitAudioDevice();
    pianoTrack = LoadMusicStream("src/resources/music/piano.wav");
    PlayMusicStream(pianoTrack);
    SetMusicVolume(pianoTrack, 1.0f);

}

void MusicPlayer::play(GameData& gameData){
    UpdateMusicStream(pianoTrack);
}

MusicPlayer::~MusicPlayer(){
    UnloadMusicStream(pianoTrack);
    CloseAudioDevice();
}