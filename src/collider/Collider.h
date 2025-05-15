#pragma once

#include "raylib.h"

enum class ColliderType{
    NONE,
    CIRCLE,
    LINE_SEGMENT,
};

struct Collider{
    ColliderType type = ColliderType::NONE;
    Vector2 p0{0, 0};
    Vector2 p1{0, 0};
    float radius = 0;
};

Collider MakeLineCollider(Vector2 p0, Vector2 p1);
Collider MakeCircleCollider(Vector2 p0, float radius);