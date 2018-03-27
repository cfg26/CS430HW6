#include "Face.h"
#include "Vertice.h"
#include <vector>

Face::Face(std::vector<Vertice*> verticeList)
{

	vertice1 = verticeList[0];
	vertice2 = verticeList[1];
	vertice3 = verticeList[2];
}

Face::~Face()
{
}
