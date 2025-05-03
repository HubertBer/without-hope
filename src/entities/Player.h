#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../GameData.h"
#include <vector>
#include "../weapons/Weapon.h"

class Weapon;

struct Player : public Entity{
public:
    Player(Vector2 prevPos, Vector2 pos, Vector2 velocity);
    void physicsUpdate(GameData& game) override;
    void gameUpdate(GameData& game, float dt) override;
    void collide(std::shared_ptr<Entity> entity,GameData& gameData) override;
    void draw() override;
    EntityType type() override;

    static constexpr float BASE_RADIUS =30.f;
    static constexpr float maxSpeed = 500.0f;

private:
    std::vector<std::shared_ptr<Weapon>> weapons;
};