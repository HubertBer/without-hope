#pragma once

#include <raylib.h>
#include "../GameData.h"
#include "../entities/Entity.h"
#include "../screens/Screen.h"
#include <map>


class SoundLoader{
public:
    static std::map<std::string,Sound> audio;
    static void load();
    static void unload();
private:
};
