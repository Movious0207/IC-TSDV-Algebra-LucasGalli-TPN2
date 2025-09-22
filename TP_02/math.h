#pragma once

#include <cmath>
#include <include/raylib.h>

Vector3 GetCrossProduct(Vector3 v1, Vector3 v2);
float GetMagnitude(Vector3 v);
Vector3 GetNormalized(Vector3 v);
Vector3 GetVectorsSum(Vector3 v1, Vector3 v2);
Vector3 GetVectorsSub(Vector3 v1, Vector3 v2);

