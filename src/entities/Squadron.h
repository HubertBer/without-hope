#pragma once

#include <raylib.h>
#include "Entity.h"
#include <vector>
#include <array>
#include "SquadronShip.h"

class Squadron : public Entity{
public:
    Squadron(Vector2 pos, float rotation, bool hasSplit = false, Vector2 shipsOffset = Vector2{0, 0}, const std::vector<std::weak_ptr<SquadronShip>>& ships = {});
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void start(GameData& game) override;
    void collide(std::shared_ptr<Entity> entity,GameData& gameData) override;
    void draw() override;
    EntityType type() override;

private:
    void repositionShips();
    void split(GameData& game);

    Vector2 shipsOffset{0, 0};
    std::vector<std::weak_ptr<SquadronShip>> ships;
    bool hasSplit = false;

    static constexpr int SQUADRON_SIZE = 15;
    static constexpr float Y_OFFSET = 40.f;
    static constexpr float X_OFFSET = 25.f;
    static constexpr float SPLIT_DISTANCE = 400.f;
    static constexpr float MAX_SPEED = 450.f;
    std::array<Vector2, SQUADRON_SIZE> offset{};
};