#pragma once
#include <iostream>
#include "Line.h"
#include "Vertice.h"
#include "Face.h"
#include <vector>

using namespace std;

class Polygon
{
public:
	Polygon(Face* polygonFace);
	void printPolygon();
	~Polygon();
	vector <Line*> polyLines;
	vector <Vertice*> pixels;
};

