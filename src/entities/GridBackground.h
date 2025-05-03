#pragma once

#include "raylib.h"
#include "Entity.h"
#include "../GameData.h"

class GridBackground : public Entity{
public:
    GridBackground();
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> entity, GameData& gameData) override;
    void draw() override;
    EntityType type() override;

private:
    Rectangle cameraBoundaries;

    static constexpr float lineWidth = 5.f;
    static constexpr float lineSpacing = 50.f;
    static constexpr Color color = GRAY;
};