#include "LinearAlgebra.h"

#include <cmath>

Vector3 sphericalToCartesian(Vector2 polarCoords) {
	float theta = polarCoords.x;
	float phi = polarCoords.y;

	float x = cos(theta) * sin(phi);
	float y = sin(theta) * sin(phi);
	float z = cos(phi);

	return {x, y, z};
}

Vector2 cartesianToSpherical(Vector3 cartesianCoords) {
	float x = cartesianCoords.x;
	float y = cartesianCoords.y;
	float z = cartesianCoords.z;

	float theta = atan2(y, x); // azimuthal angle
	float phi = acos(z / sqrt(x * x + y * y + z * z)); // polar angle

	return {theta, phi};
}

Vector3 cross(Vector3 a, Vector3 b) {
  return {a.y * b.z - a.z * b.y,
      a.z * b.x - a.x * b.z,
      a.x * b.y - a.y * b.x};
}

float dot(Vector3 a, Vector3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}