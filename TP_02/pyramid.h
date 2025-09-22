#pragma once

#include <include/raylib.h>
#include <include/raymath.h>
#include <vector>
#include "math.h"

struct Floor
{
	Vector3 edges[8] = {};
};

struct Pyramid
{
	std::vector<Floor> floors;
};

std::vector <Pyramid> CreatePyramid(Vector3 origin, Vector3 a, Vector3 b, Vector3 c, int pyramidAmount);
int GetFloorAmount(Vector3 a, Vector3 c);
float GetXYLength(Vector3 c);
float GetPerimeter(Pyramid pyramid);
float GetAreaDec(Pyramid pyramid);
float GetAreaCrec(Pyramid pyramid);
float GetVolume(Pyramid pyramid);