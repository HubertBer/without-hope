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
    int getScore() override;

private:
    Vector2 target;
    bool fuckIt = false;
    static constexpr float FUCK_IT_DISTANCE = 150.f; 
    static constexpr float MAX_SPEED = 650.f;
    static constexpr float RADIUS = 12.f;
    static constexpr int SCORE = 2;
    static constexpr float DEFAULT_VELOCITY_MODIFIER = 1.0f;
    float velocityModifier=1.0f;
    float velocityModifierDuration=0.0f;
};