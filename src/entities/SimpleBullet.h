#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../GameData.h"

struct SimpleBullet : public Entity {
public:
    SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity, float rotation, EntityType parent_type = PLAYER, Color color = WHITE);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> other, GameData& gameData) override;
    void draw() override;
    EntityType type() override;

    static constexpr float BASE_RADIUS =10.f;
    static constexpr float maxSpeed = 800.f;
    
private:
    EntityType parent_type;

    // Needed for the enemy bullets to vanish properly
    // as they ignore map boundaries (makes more sense for them) 
    float lifetime = 10.f;
    static constexpr float DEFAULT_VELOCITY_MODIFIER = 1.0f;
    float velocityModifier=1.0f;
    float velocityModifierDuration=0.0f;
};