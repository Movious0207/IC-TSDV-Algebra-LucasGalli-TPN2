#include <include/raylib.h>
#include <include/raymath.h>
#include <iostream>
#include "math.h"
#include "pyramid.h"

int main(void)
{
	SetRandomSeed(time(0));

	const int screenWidth = 800;
	const int screenHeight = 450;

	const int minRan = 5;
	const int maxRan = 10;

	Vector3 origin{ 0,0,0 };

	Camera3D camera = { 0 };

	const float cameraDistance = 20.0f;
	const float rotationAngle = 3.0f;

	camera.position = { cameraDistance, cameraDistance, cameraDistance };  // Camera position
	camera.target = origin;      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

	float userInputCSize = 10.0f;

	int userInputPyrAmount = 1;

	Vector3 baseX = { 10, origin.y, origin.z };
	Vector3 baseY = { origin.x, 10, origin.z };
	Vector3 baseZ = { origin.x, origin.y, 10 };

	Vector3 a = {};

	a.x = GetRandomValue(minRan, maxRan);
	a.y = GetRandomValue(minRan, maxRan);
	a.z = GetRandomValue(minRan, maxRan);

	Vector3 b = { a.y, -a.x, 0 };

	b = GetNormalized(b) * GetMagnitude(a);

	Vector3 c = {};

	std::vector<Pyramid> pyramids;

	bool validAnswer = false;
		
	validAnswer = false;
	std::cout << "Ingrese cuanto quiere que sea N: ";
	while (!validAnswer) {
		std::cin >> userInputCSize;
			validAnswer = true;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX,'\n');
			validAnswer = false;
		}
		if (userInputCSize <= 0) {
			validAnswer = false;
		}
	}
	std::cout << std::endl;

	validAnswer = false;
	std::cout << "Ingrese cuantas piramides quiere: ";
	while (!validAnswer) {
		std::cin >> userInputPyrAmount;
		validAnswer = true;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			validAnswer = false;
		}
		if (userInputPyrAmount <= 0) {
			validAnswer = false;
		}
	}

	userInputCSize += 5.0f;

	c = GetCrossProduct(a, b);

	c = GetNormalized(c) * ((1.0f / userInputCSize) * GetMagnitude(a));

	pyramids = CreatePyramid(origin, a, b, c, userInputPyrAmount);

	float deltaTime = 0;

	for (int floor = 0; floor < pyramids[0].floors.size(); floor++)
	{
		for (int edge = 0; edge < 8; edge++)
		{
			std::cout << "Piso: " << floor << "  ";
			std::cout << "Esquina: " << edge << "  ";
			std::cout << "Pos x: " << pyramids[0].floors[floor].edges[edge].x << "  ";
			std::cout << "Pos y: " << pyramids[0].floors[floor].edges[edge].y << "  ";
			std::cout << "Pos z: " << pyramids[0].floors[floor].edges[edge].z;
		}
		std::cout << std::endl << std::endl;
	}

	for (int pyramid = 0; pyramid < pyramids.size(); pyramid++)
	{
		std::cout << "Piramide " << pyramid << std::endl;
		std::cout << "Perimetro: " << GetPerimeter(pyramids[pyramid]) << std::endl;

		if (pyramid % 2 != 0)
		{
			std::cout << "Area: " << GetAreaCrec(pyramids[pyramid]) << std::endl;
		}
		else
		{
			std::cout << "Area: " << GetAreaDec(pyramids[pyramid]) << std::endl;
		}

		std::cout << "Volumen: " << GetVolume(pyramids[pyramid]) << std::endl << std::endl;
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "TP02");

	while (!WindowShouldClose())
	{
		deltaTime = GetFrameTime();

		//Camera movement
		if (IsKeyDown(KEY_UP))
		{
			camera.position = Vector3RotateByAxisAngle(camera.position, { -baseX.x, baseX.y, baseX.z }, rotationAngle * deltaTime);
		}

		if (IsKeyDown(KEY_DOWN))
		{
			camera.position = Vector3RotateByAxisAngle(camera.position, { baseX.x, baseX.y, baseX.z }, rotationAngle * deltaTime);
		}

		if (IsKeyDown(KEY_LEFT))
		{
			camera.position = Vector3RotateByAxisAngle(camera.position, { baseY.x, baseY.y, baseY.z }, rotationAngle * deltaTime);
		}

		if (IsKeyDown(KEY_RIGHT))
		{
			camera.position = Vector3RotateByAxisAngle(camera.position, { baseY.x, -baseY.y, baseY.z }, rotationAngle * deltaTime);
		}

		GetNormalized(baseX);

		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode3D(camera);

		//draw base
		DrawLine3D(origin, baseX, BLUE);
		DrawLine3D(origin, baseY, GREEN);
		DrawLine3D(origin, baseZ, RED);

		//draw vectorABC
		DrawLine3D(origin, a, VIOLET);
		DrawLine3D(origin, b, SKYBLUE);
		DrawLine3D(origin, c, YELLOW);

		//Marca puntos en cada uno de los vertices
		/*
		for (int floor = 0; floor < pyramids[0].floors.size(); floor++)
		{
			for (int edge = 0; edge < 8; edge++)
			{
				DrawSphere(pyramids[0].floors[floor].edges[edge], 0.15, RED);
			}
		}
		*/


		Color pyrColor;

		for (int curPyramid = 0; curPyramid < userInputPyrAmount; curPyramid++)
		{
			if (curPyramid % 2 == 0)
			{
				pyrColor = RED;
			}
			else
			{
				pyrColor = BLUE;
			}

			for (int floor = 0; floor < pyramids[curPyramid].floors.size(); floor++)
			{
				//Crea lineas entre todos los vertices de una cara, menos la ultima que conecta de vuelta con 0
				for (int face = 0; face < 3; face++)
				{
					DrawLine3D(pyramids[curPyramid].floors[floor].edges[0 + face], pyramids[curPyramid].floors[floor].edges[1 + face], pyrColor);
					DrawLine3D(pyramids[curPyramid].floors[floor].edges[1 + face], pyramids[curPyramid].floors[floor].edges[1 + 4 + face], pyrColor);
					DrawLine3D(pyramids[curPyramid].floors[floor].edges[1 + 4 + face], pyramids[curPyramid].floors[floor].edges[0 + 4 + face], pyrColor);
					DrawLine3D(pyramids[curPyramid].floors[floor].edges[0 + 4 + face], pyramids[curPyramid].floors[floor].edges[0 + face], pyrColor);
				}
				//Ultima cara
				DrawLine3D(pyramids[curPyramid].floors[floor].edges[3], pyramids[curPyramid].floors[floor].edges[0], pyrColor);
				DrawLine3D(pyramids[curPyramid].floors[floor].edges[0], pyramids[curPyramid].floors[floor].edges[4], pyrColor);
				DrawLine3D(pyramids[curPyramid].floors[floor].edges[4], pyramids[curPyramid].floors[floor].edges[7], pyrColor);
				DrawLine3D(pyramids[curPyramid].floors[floor].edges[7], pyramids[curPyramid].floors[floor].edges[3], pyrColor);
			}
		}


		EndMode3D();

		EndDrawing();

	}


	CloseWindow();

	return 0;
}