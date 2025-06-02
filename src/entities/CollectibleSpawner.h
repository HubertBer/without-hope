#pragma once

#include "Entity.h"

class CollectibleSpawner : public Entity {
public:
    CollectibleSpawner();
    void gameUpdate(GameData& game, float dt) override;

    int next_threshold = 200;
    static constexpr int SCORE_THRESHOLD = 300;
};