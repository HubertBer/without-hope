#pragma once

#include <raylib.h>

#include "Entity.h"
#include "../GameData.h"

struct SimpleBullet : public Entity {
public:
    SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity, float rotation);
    void gameUpdate(GameData& game, float dt) override;
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData) override;
    void draw() override;
    void start(GameData&) override;
    EntityType type() override;

    static constexpr float BASE_RADIUS =10.f;
    static constexpr float maxSpeed = 800.f;

private:
    std::shared_ptr<Collider> collider;
};