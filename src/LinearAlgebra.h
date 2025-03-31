#pragma once

#include <raylib.h>

Vector3 sphericalToCartesian(Vector2 polarCoords);
Vector2 cartesianToSpherical(Vector3 cartesianCoords);
Vector3 cross(Vector3 a, Vector3 b);
float dot(Vector3 a, Vector3 b);