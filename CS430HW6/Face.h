#pragma once
#include "Vertice.h"
#include <vector>
class Face
{
public:
	Face(std::vector<Vertice*> verticeList);
	~Face();

	Vertice* vertice1;
	Vertice* vertice2;
	Vertice* vertice3;
	
};

