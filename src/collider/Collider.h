#pragma once

#include "raylib.h"
#include "../entities/Entity.h"

class Entity;
struct Collider{
    static enum class Type{
        CIRCLE,
        LINE_SEGMENT,
    };

    Type type = Type::CIRCLE;
    Vector2 p0{0, 0};
    Vector2 p1{0, 0};
    float radius = 0;
};

Collider MakeLineCollider(Vector2 p0, Vector2 p1);
Collider MakeCircleCollider(Vector2 p0, float radius);