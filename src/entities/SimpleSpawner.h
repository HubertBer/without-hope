#pragma once

#include "Entity.h"
#include "../GameData.h"

class SimpleSpawner : public Entity{
public:
    SimpleSpawner(Rectangle boundingBox, float minDelay, float maxDelay);
    void gameUpdate(GameData& game, float dt) override;

private:
    float timer = 0;
    Rectangle boundingBox = {0,0,0,0};
    float minDelay = 5;
    float maxDelay = 10;
};