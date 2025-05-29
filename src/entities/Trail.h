#pragma once

#include <memory>
#include "Entity.h"
#include "raylib.h"

class Trail : public Entity{
public:
    Trail(std::weak_ptr<Entity> target, float thickness = THICKNESS, float distance = DISTANCE, Color color = WHITE, bool dashed = false, bool contour = false, Color contourColor = BLACK);
    void draw() override;
    void gameUpdate(GameData&, float dt) override;
    void physicsUpdate(GameData&);
private:
    float lerpThickness(float timer);
    
    bool pointParity = false;
    float fadeAwayTimer = LIFETIME;

    const float thickness = THICKNESS;
    const float distance = DISTANCE;
    const bool dashed = false;
    const bool contour = false;
    const Color color = WHITE;
    const Color contourColor = BLACK;

    std::weak_ptr<Entity> target;
    Vector2 lastPos;
    static constexpr int MAX_POINTS = 32;
    static constexpr int IGNORE_POINTS = 2;
    static constexpr float LIFETIME = 0.4f;
    static constexpr float DISTANCE = 5.f;
    static constexpr float THICKNESS = 6.f;
    static constexpr float CONTOUR_THICKNESS_MOD = 1.8f;

    struct TrailPoint{
        Vector2 pos{0.f,0.f};
        float timer{LIFETIME};
    };
    TrailPoint points[MAX_POINTS]{TrailPoint{Vector2{0,0}, 0}};
};