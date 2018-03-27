#include "Polygon.h"
#include <iostream>




Polygon::Polygon(Face * polygonFace)
{
	Line* line1 = new Line(polygonFace->vertice1->xCoord, polygonFace->vertice1->yCoord, polygonFace->vertice1->zCoord, polygonFace->vertice2->xCoord, polygonFace->vertice2->yCoord, polygonFace->vertice2->zCoord);
	Line* line2 = new Line(polygonFace->vertice2->xCoord, polygonFace->vertice2->yCoord, polygonFace->vertice2->zCoord, polygonFace->vertice3->xCoord, polygonFace->vertice3->yCoord, polygonFace->vertice3->zCoord);
	Line* line3 = new Line(polygonFace->vertice3->xCoord, polygonFace->vertice3->yCoord, polygonFace->vertice3->zCoord, polygonFace->vertice1->xCoord, polygonFace->vertice1->yCoord, polygonFace->vertice1->zCoord);

	polyLines.push_back(line1);
	polyLines.push_back(line2);
	polyLines.push_back(line3);

}

void Polygon::printPolygon(){
	for (int i = 0; i < this->polyLines.size(); i++) {
		cout << "Line " << i << endl;
		cout << this->polyLines[i]->x1 << " " << this->polyLines[i]->y1 << " " << this->polyLines[i]->z1 << " " << endl;
		cout << this->polyLines[i]->x2 << " " << this->polyLines[i]->y2 << " " << this->polyLines[i]->z2 << " " << endl;
	}
		
}

Polygon::~Polygon()
{
}