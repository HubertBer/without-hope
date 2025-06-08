#pragma once

#include "Entity.h"

enum class WeaponType{
    MAIN,
    AUTOMATIC,
    SPECIAL,
    HEALTH,
};

class Collectible : public Entity{
public:
    Collectible(Vector2 pos, bool playerDamaged);
    void physicsUpdate(GameData& game) override;
    void collide(std::shared_ptr<Entity> other, GameData& gameData) override;
    void draw() override;
    void start(GameData&) override;
    EntityType type() override;
    WeaponType weapon;

private:
    void loadProperTexture();

    Vector2 target;


    float life_timer;
    float change_timer;

    static constexpr float MAX_SPEED = 200.f;
    static constexpr float CHANGE_COOLDOWN = 6.f;
    static constexpr float LIFETIME = 24.f;
    static constexpr float BASE_RADIUS = 30.f;
};