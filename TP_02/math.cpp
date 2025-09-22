#include "math.h"
#include <include/raylib.h>

Vector3 GetCrossProduct(Vector3 v1, Vector3 v2)
{
	Vector3 result = { (v1.y * v2.z - v1.z * v2.y), -(v1.x * v2.z - v1.z * v2.x), (v1.x * v2.y - v1.y * v2.x) };

	return result;
}

float GetMagnitude(Vector3 v)
{
	float magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	return magnitude;
}

Vector3 GetNormalized(Vector3 v)
{
	Vector3 normalized = v;

	float magnitude = GetMagnitude(v);

	if (magnitude != 0)
	{
		normalized.x /= magnitude;
		normalized.y /= magnitude;
		normalized.z /= magnitude;
	}
	else
	{
		return { 0,0,0 };
	}

	return normalized;
}

Vector3 GetVectorsSum(Vector3 v1, Vector3 v2)
{
	Vector3 sum = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };

	return sum;
}

Vector3 GetVectorsSub(Vector3 v1, Vector3 v2)
{
	Vector3 sub = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };

	return sub;
}
