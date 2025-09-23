#include "pyramid.h"

std::vector <Pyramid> CreatePyramid(Vector3 origin, Vector3 a, Vector3 b, Vector3 c, int pyramidAmount)
{
	//guarda los vectores normalizados para usar luego la magnitud de los que recibe por parametro
	Vector3 normA = GetNormalized(a);
	Vector3 normB = GetNormalized(b);
	Vector3 normC = GetNormalized(c);

	std::vector<Pyramid> pyramids;

	for (int i = 0; i < pyramidAmount; i++)
	{
		Pyramid pyramid;

		pyramids.push_back(pyramid);
	}

	for (int curPyramid = 0; curPyramid < pyramidAmount; curPyramid++)
	{
		if (curPyramid == 0) //Si es la primera piramide
		{
			float xyLength = 0;

			//calcula cuantos pisos va a necesitar
			int floorAmount = GetFloorAmount(a, c);

			//genera la cantidad de pisos que va a necesitar
			for (int i = 0; i < floorAmount; i++)
			{
				Floor floor;

				pyramids[curPyramid].floors.push_back(floor);
			}

			for (int curFloor = 0; curFloor < floorAmount; curFloor++)
			{
				//genera un piso
				Floor floor = pyramids[curPyramid].floors[curFloor];

				//Setea el origen
				floor.edges[0] = GetVectorsSum(floor.edges[0], normA * xyLength * curFloor);
				floor.edges[0] = GetVectorsSum(floor.edges[0], normB * xyLength * curFloor);
				floor.edges[0] = GetVectorsSum(floor.edges[0], normC * xyLength * curFloor);


				floor.edges[1] = floor.edges[0]; //Setea el vector en su origen correspondiente
				floor.edges[1] = GetVectorsSum(floor.edges[1], normA * (GetMagnitude(a) - xyLength * (2 * curFloor))); //En su posicion correspondiente

				floor.edges[2] = floor.edges[0];
				floor.edges[2] = GetVectorsSum(floor.edges[2], normA * (GetMagnitude(a) - xyLength * (2 * curFloor)));
				floor.edges[2] = GetVectorsSum(floor.edges[2], normB * (GetMagnitude(b) - xyLength * (2 * curFloor)));

				floor.edges[3] = floor.edges[0];
				floor.edges[3] = GetVectorsSum(floor.edges[3], normB * (GetMagnitude(b) - xyLength * (2 * curFloor)));


				//Setea las demas esquinas del piso, mismas 4 que la base pero c mas arriba
				floor.edges[4] = GetVectorsSum(floor.edges[0], c);
				floor.edges[5] = GetVectorsSum(floor.edges[1], c);
				floor.edges[6] = GetVectorsSum(floor.edges[2], c);
				floor.edges[7] = GetVectorsSum(floor.edges[3], c);

				//Calcula la distancia en x e y que forma aquella mangitud c, siendo magnitud c la hipotenusa.
				xyLength = GetXYLength(c);

				//pushea el piso armado
				pyramids[curPyramid].floors[curFloor] = floor;
			}
		}
		else if (curPyramid % 2 != 0)//Si es creciente
		{
			float xyLength = 0;

			//calcula cuantos pisos va a necesitar
			int floorAmount = GetFloorAmount(a, c) - 1;

			//genera la cantidad de pisos que va a necesitar
			for (int i = 0; i < floorAmount; i++)
			{
				Floor floor;

				pyramids[curPyramid].floors.push_back(floor);
			}

			for (int curFloor = 0; curFloor < floorAmount; curFloor++)
			{

				Floor floor = pyramids[curPyramid].floors[curFloor];

				//Toma como punto de inicio la esquina superior del ultimo piso de la anterior piramide
				floor.edges[0] = pyramids[curPyramid - 1].floors[pyramids[curPyramid - 1].floors.size() - 1].edges[4];

				//al punto de inicio le resta en a y b magnitud c, para que quede a la distancia que le corresponderia para continuar la figura
				floor.edges[0] = GetVectorsSub(floor.edges[0], normA * GetMagnitude(c));
				floor.edges[0] = GetVectorsSub(floor.edges[0], normB * GetMagnitude(c));

				floor.edges[0] = GetVectorsSum(floor.edges[0], normA * -xyLength * curFloor);
				floor.edges[0] = GetVectorsSum(floor.edges[0], normB * -xyLength * curFloor);
				floor.edges[0] = GetVectorsSum(floor.edges[0], normC * xyLength * curFloor);

				floor.edges[1] = floor.edges[0];
				floor.edges[1] = GetVectorsSum(floor.edges[1], normA * (GetMagnitude(a) - (GetXYLength(c) * 2 * (floorAmount - 1)) + xyLength * 2 * curFloor)); //En su posicion correspondiente

				floor.edges[2] = floor.edges[0];
				floor.edges[2] = GetVectorsSum(floor.edges[2], normA * (GetMagnitude(a) - (GetXYLength(c) * 2 * (floorAmount - 1)) + xyLength * 2 * curFloor));
				floor.edges[2] = GetVectorsSum(floor.edges[2], normB * (GetMagnitude(b) - (GetXYLength(c) * 2 * (floorAmount - 1)) + xyLength * 2 * curFloor));

				floor.edges[3] = floor.edges[0];
				floor.edges[3] = GetVectorsSum(floor.edges[3], normB * (GetMagnitude(b) - (GetXYLength(c) * 2 * (floorAmount - 1)) + xyLength * 2 * curFloor));

				floor.edges[4] = GetVectorsSum(floor.edges[0], c);
				floor.edges[5] = GetVectorsSum(floor.edges[1], c);
				floor.edges[6] = GetVectorsSum(floor.edges[2], c);
				floor.edges[7] = GetVectorsSum(floor.edges[3], c);

				xyLength = GetXYLength(c);

				pyramids[curPyramid].floors[curFloor] = floor;
			}
		}
		else if (curPyramid % 2 == 0) //Si es decreciente
		{
			float xyLength = 0;

			int floorAmount = GetFloorAmount(a, c) - 1;

			for (int i = 0; i < floorAmount; i++)
			{
				Floor floor;

				pyramids[curPyramid].floors.push_back(floor);
			}

			for (int curFloor = 0; curFloor < floorAmount; curFloor++)
			{

				Floor floor = pyramids[curPyramid].floors[curFloor];

				//Toma como punto de inicio la posicion de la primera esquina del penultimo piso de la ultima piramide, (la esq de arriba)
				floor.edges[0] = pyramids[curPyramid - 1].floors[pyramids[curPyramid - 1].floors.size() - 2].edges[4];
				
				//le suma c
				floor.edges[0] = GetVectorsSum(floor.edges[0], c);

				floor.edges[0] = GetVectorsSum(floor.edges[0], normA * xyLength * curFloor);
				floor.edges[0] = GetVectorsSum(floor.edges[0], normB * xyLength * curFloor);
				floor.edges[0] = GetVectorsSum(floor.edges[0], normC * xyLength * curFloor);

				floor.edges[1] = floor.edges[0];
				floor.edges[1] = GetVectorsSum(floor.edges[1], normA * (GetMagnitude(a) - GetXYLength(c) * 2 - xyLength * (2 * curFloor)));

				floor.edges[2] = floor.edges[0];
				floor.edges[2] = GetVectorsSum(floor.edges[2], normA * (GetMagnitude(a) - GetXYLength(c) * 2 - xyLength * (2 * curFloor)));
				floor.edges[2] = GetVectorsSum(floor.edges[2], normB * (GetMagnitude(b) - GetXYLength(c) * 2 - xyLength * (2 * curFloor)));

				floor.edges[3] = floor.edges[0];
				floor.edges[3] = GetVectorsSum(floor.edges[3], normB * (GetMagnitude(b) - GetXYLength(c) * 2 - xyLength * (2 * curFloor)));

				floor.edges[4] = GetVectorsSum(floor.edges[0], c);
				floor.edges[5] = GetVectorsSum(floor.edges[1], c);
				floor.edges[6] = GetVectorsSum(floor.edges[2], c);
				floor.edges[7] = GetVectorsSum(floor.edges[3], c);

				xyLength = GetXYLength(c);


				pyramids[curPyramid].floors[curFloor] = floor;
			}
		}
	}

	return pyramids;
}

int GetFloorAmount(Vector3 a, Vector3 c) //hace el calculo en base a cuantas veces entra xyLength * 2 en la magnitud de a y lo trunca para sacar el valor real
{
	int floors = 0;

	float xyLength = GetXYLength(c);

	floors = std::trunc(GetMagnitude(a) / (2 * xyLength));

	return floors;
}

float GetXYLength(Vector3 c)
{
	float xyLength = 0.0f;

	xyLength = sin(45) * GetMagnitude(c);

	return xyLength;
}

float GetPerimeter(Pyramid pyramid)
{
	float perimeter = 0.0f;

	for (int floor = 0; floor < pyramid.floors.size(); floor++)
	{
		//Cara de arriba
		perimeter += GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1])) * 4;

		//Cara de abajo
		perimeter += GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[4], pyramid.floors[floor].edges[5])) * 4;

		//Caras de los lados
		perimeter += GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1])) * 2 * 4;
		perimeter += GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[4])) * 2 * 4;
	}

	return perimeter;
}

float GetAreaDec(Pyramid pyramid) //para piramides decrecientes
{
	float area = 0.0f;

	for (int floor = 0; floor < pyramid.floors.size(); floor++)
	{
		if (floor == 0)
		{
			area += (GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1]))
				* GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1])));
		}

		area += (GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[4], pyramid.floors[floor].edges[5]))
			* GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[4], pyramid.floors[floor].edges[5])));

		if (floor < pyramid.floors.size() - 1)
		{
			area -= (GetMagnitude(GetVectorsSub(pyramid.floors[floor + 1].edges[4], pyramid.floors[floor + 1].edges[5]))
				* GetMagnitude(GetVectorsSub(pyramid.floors[floor + 1].edges[4], pyramid.floors[floor + 1].edges[5])));
		}

		area += (GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1]))
			* GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[4]))) * 4;
	}

	return area;
}

float GetAreaCrec(Pyramid pyramid) //para piramides crecientes
{
	float area = 0.0f;

	for (int floor = 0; floor < pyramid.floors.size(); floor++)
	{
		if (floor == pyramid.floors.size() - 1)
		{
			area += (GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[4], pyramid.floors[floor].edges[5]))
				* GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[4], pyramid.floors[floor].edges[5])));
		}

		area += (GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1]))
			* GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1])));

		if (floor > 0)
		{
			area -= (GetMagnitude(GetVectorsSub(pyramid.floors[floor - 1].edges[4], pyramid.floors[floor - 1].edges[5]))
				* GetMagnitude(GetVectorsSub(pyramid.floors[floor - 1].edges[4], pyramid.floors[floor - 1].edges[5])));
		}

		area += (GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1]))
			* GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[4]))) * 4;
	}

	return area;
}

float GetVolume(Pyramid pyramid)
{
	float volume = 0.0f;

	for (int floor = 0; floor < pyramid.floors.size(); floor++)
	{
		volume += (GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[1]))
			* GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[3]))
			* GetMagnitude(GetVectorsSub(pyramid.floors[floor].edges[0], pyramid.floors[floor].edges[4])));
	}

	return volume;
}