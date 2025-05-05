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
    void collide(std::shared_ptr<Collider> ownCollider, std::pair<std::weak_ptr<Entity>, std::weak_ptr<Collider>> other, GameData& gameData) override;
    void draw() override;
    void start(GameData&) override;
    EntityType type() override;

    static constexpr float BASE_RADIUS =30.f;
    static constexpr float maxSpeed = 500.0f;
    static constexpr float maxAcceleration = 1500.0f;
    static constexpr float friction = 0.5f;
private:
    Vector2 acceleration{0.f, 0.f};
    std::shared_ptr<Collider> collider;
    std::vector<std::shared_ptr<Weapon>> weapons;
};