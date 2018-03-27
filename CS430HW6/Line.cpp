#include "Line.h"
#include <iostream>

using namespace std;

Line::Line(float x11, float y11, float z11, float x22, float y22, float z22)
{
	x1 = x11;
	x2 = x22;
	y1 = y11;
	y2 = y22;
	z1 = z11;
	z2 = z22;
}

Line::~Line()
{
}

void Line::printLineInfo()
{
	cout << x1 << " " << x2 << " " << y1 << " " << y2 << " " << endl;
}
