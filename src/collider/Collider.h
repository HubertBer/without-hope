#pragma once

#include "raylib.h"

enum class ColliderType{
    NONE,
    CIRCLE,
    LINE_SEGMENT,
    CIRCLE_OUTLINE,
};

struct Collider{
    ColliderType type = ColliderType::NONE;
    Vector2 p0{0, 0};
    Vector2 p1{0, 0};
    float radius = 0;
    float inside_radius=0;
};

Collider MakeLineCollider(Vector2 p0, Vector2 p1);
Collider MakeCircleCollider(Vector2 p0, float radius);
Collider MakeCircleOutlineCollider(Vector2 p0, float radius,float inside_radius);