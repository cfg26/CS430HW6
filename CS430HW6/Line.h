#pragma once
#include <iostream>
class Line
{
public:
	Line(float x11, float y11, float z11, float x22, float y22, float z22);
	~Line();
	void printLineInfo();
	float x1;
	float x2;
	float y1;
	float y2;
	float z1;
	float z2;
};
