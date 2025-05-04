#include "Collider.h"
#include "raylib.h"

Collider MakeLineCollider(Vector2 p0, Vector2 p1){
    return Collider{
        Collider::Type::LINE_SEGMENT,
        p0,
        p1,
        0.0f
    }; 
}

Collider MakeCircleCollider(Vector2 p0, float radius){
    return Collider{
        Collider::Type::CIRCLE,
        p0,
        Vector2{0, 0},
        radius
    };
}