#include <utility>
#include <cmath>

#include <raylib.h>
#include <raymath.h>

#include "LinearAlgebra.h"

Vector2 rotateTheta(Vector2 polarCoords, float theta) {
    return {polarCoords.x + theta, polarCoords.y};
}

// Rotate the polar coordinates by an angle phi around the y-axis
Vector2 rotatePhi(Vector2 polarCoords, float phi) {
	Vector3 cart = sphericalToCartesian(polarCoords);
	Vector3 rotationAxis = {0, 1, 0};

    Vector3 res = cart * cos(phi) + cross(rotationAxis, cart) * sin(phi) + rotationAxis * dot(rotationAxis, cart) * (1 - cos(phi));

    return cartesianToSpherical(res);
}

constexpr float scale = 250.f;

Vector2 movePlayer(Vector2 pos, Vector2 velocity) {
    // Move the player as if it was at (0, PI/2) (equator), and then translate back.
    // This is approximate at the moment, assuming that at the equator 
    // one unit to the left and up will always be the same as just one unit to the left.


    Vector2 translated{0, PI/2};

    // return rotatePhi(rotateTheta(velocity, pos.x), pos.y - PI/2);
    return rotateTheta(rotatePhi(translated + velocity, (pos.y - PI/2)), pos.x);
}

Vector2 stereographicProjection(Vector2 polarCoords, Vector2 center) {
    Vector2 translated = rotatePhi(rotateTheta(polarCoords, -center.x), -center.y);
    float theta = translated.x;
    float phi = translated.y;

    Vector3 cartesianCoords = sphericalToCartesian(translated);
    float x = cartesianCoords.x;
    float y = cartesianCoords.y;
    float z = cartesianCoords.z;

    // Stereographic projection from the sphere to the plane
    double k = scale / (1.0 + z);
    double x_proj = k * x;
    double y_proj = k * y;

    return {(float)(x_proj), (float)(y_proj)};
}