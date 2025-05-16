#pragma once

#include <raylib.h>
#include <map>
#include "../GameData.h"
#include "../entities/Entity.h"
#include "../screens/Screen.h"


class MusicData{
public:
    MusicData(){}
    MusicData(Music audio):audio(audio){
        volume =1.0f;
    }
    MusicData(Music audio, float volume):audio(audio),volume(volume){};

    operator Music() const{
        return audio;
    }
    float volume = 1.0f;
private:
    Music audio;
    
};

class MusicPlayer {
public:
    MusicPlayer(bool& musicOn);
    ~MusicPlayer();

    void play(ScreenType currentScreenType);
private:
    MusicData baseMusic;
    MusicData melody;
    bool& musicOn;
    static constexpr float fadeawaySpeed = 0.002f;
};