#include "Collider.h"
#include "raylib.h"

Collider MakeLineCollider(Vector2 p0, Vector2 p1){
    return Collider{
        ColliderType::LINE_SEGMENT,
        p0,
        p1,
        0.0f
    }; 
}

Collider MakeCircleCollider(Vector2 p0, float radius){
    return Collider{
        ColliderType::CIRCLE,
        p0,
        Vector2{0, 0},
        radius
    };
}

Collider MakeCircleOutlineCollider(Vector2 p0, float radius,float inside_radius){
    return Collider{
        ColliderType::CIRCLE_OUTLINE,
        p0,
        Vector2{0, 0},
        radius,
        inside_radius,
    };
}