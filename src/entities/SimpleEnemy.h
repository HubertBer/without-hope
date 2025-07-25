#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../collider/Collider.h"
#include "../music/SoundLoader.h"

class SimpleEnemy : public Entity{
public:
    SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> other, GameData& gameData) override;
    void draw() override;
    EntityType type() override;
    virtual int getScore() override{return score;}
    void onDeath();

private:
    static constexpr float BASE_RADIUS = 10.f;
    static constexpr float maxSpeed = 300.f;
    static constexpr int score = 10;
    static constexpr float DEFAULT_VELOCITY_MODIFIER = 1.0f;
    float velocityModifier=1.0f;
    float velocityModifierDuration=0.0f;
};