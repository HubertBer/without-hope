#include "SoundLoader.h"

void SoundLoader::load(){
    audio["simpleEnemyDead"] = LoadSound("src/resources/music/dead.wav");
    SetSoundVolume(audio["simpleEnemyDead"],0.25);
    audio["playerBullet"] = LoadSound("src/resources/music/bullet.wav");
    SetSoundVolume(audio["playerBullet"],0.05);
    audio["laser"] = LoadSound("src/resources/music/laser.wav");
    SetSoundVolume(audio["laser"],0.3);
    audio["squadron"] = LoadSound("src/resources/music/squadron.wav");
    SetSoundVolume(audio["squadron"],0.1);
}

void SoundLoader::unload(){
    for(auto& [s,sound]:audio){
        UnloadSound(sound);
    }
}

std::map<std::string,Sound> SoundLoader::audio;
