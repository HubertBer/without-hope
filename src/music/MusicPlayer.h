#pragma once

#include <raylib.h>
#include <map>
#include "../GameData.h"
#include "../entities/Entity.h"


class MusicData{
public:
    MusicData(){}
    MusicData(Music audio):audio(audio){
        volume =1.0f;
    }

    operator Music() const{
        return audio;
    }
    float volume = 1.0f;
private:
    Music audio;
    
};

class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();

    void play(GameData& gameData);
private:
    std::map<EntityType,MusicData> entityMusic;
    static constexpr float fadeawaySpeed = 0.002f;
};