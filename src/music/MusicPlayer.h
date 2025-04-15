#pragma once

#include <raylib.h>

#include "../GameData.h"

class MusicPlayer {
public:
    MusicPlayer();
    ~MusicPlayer();

    void play(GameData& gameData);
private:
    Music pianoTrack;
};