#pragma once

#include <memory>
#include "Entity.h"
#include "raylib.h"

class Trail : public Entity{
public:
    Trail(std::weak_ptr<Entity> target);
    void draw() override;
    void gameUpdate(GameData&, float dt) override;
    void physicsUpdate(GameData&);
private:
    float lerpThickness(float timer);

    std::weak_ptr<Entity> target;
    Vector2 lastPos;
    static constexpr int MAX_POINTS = 32;
    static constexpr int IGNORE_POINTS = 2;
    static constexpr float LIFETIME = 0.4f;
    static constexpr float DISTANCE = 5.f;
    static constexpr float THICKNESS = 6.f;
    static constexpr Color color = WHITE;

    struct TrailPoint{
        Vector2 pos{0.f,0.f};
        float timer{LIFETIME};
    };
    TrailPoint points[MAX_POINTS]{TrailPoint{Vector2{0,0}, 0}};
};