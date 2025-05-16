#pragma once
#include "Entity.h"
#include "raylib.h"

class SquadronShip : public Entity{
public:
    SquadronShip(Vector2 pos, float rotation);
    void setTarget(Vector2 target);
    void physicsUpdate(GameData& game) override;
    void gameUpdate(GameData& game, float dt) override;
    void collide(std::shared_ptr<Entity> entity,GameData& gameData) override;
    void draw() override;
    EntityType type() override;

private:
    Vector2 target;
    static constexpr float MAX_SPEED = 700.f;
    static constexpr float RADIUS = 8.f;
};