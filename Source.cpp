#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <istream>
#include <iterator>
#include <bitset>
#include <stdlib.h>
#include "Line.h"
#include "Polygon.h"
#include "Vertice.h"
#include <algorithm>
#include <string>
#include <math.h>
#include <string.h>
#include <stdio.h>

using namespace std; 


int pointCode2Giver(Line* line);
int pointCode1Giver(Line* line);
bool isFullyInside(Line* line);
bool isPointInside(int x, int y);
Vertice* intersectionOfPoints(Vertice* p1, Vertice* p2, Vertice* p3, Vertice* p4);
vector<string> printXPM(Polygon* polygon, vector<string> xpm);
vector<string> fillPolygon(Polygon* polygon, vector<string> xpm);
bool sortVector(Vertice* vertice1, Vertice* vertice2);
Polygon* scalePolygon(Polygon* polygonVector, float scaleFactor);
Polygon* rotatePolygon(Polygon* polygonVector, float scaleFactor);
Polygon* xTranslatePolygon(Polygon* polygonVector, float xTransFactor);
Polygon* yTranslatePolygon(Polygon* polygonVector, float yTransFactor);
Polygon* wwToScreen(Polygon* polygonVector, int upperx, int uppery, int lowerx, int lowery);



int main(int argc, char* argv[]) {
	string inFile = "test";
	string line = "test";
	string fileName;

	//x1 y1 x2 y2 Line
	int x1;
	int x2; 
	int y1;
	int y2;

	vector <Line*> storage;
	vector <Line*> storage2;
	vector <Line*> storage3;
	vector <Line*> storage4;
	vector <Line*> storage5;
	vector <Line*> storage6;
	vector <Line*> storage7;
	vector <Line*> storage8;
	vector <string> xpm;
	vector <string> polyLines;
	vector <string> polyLines2;
	vector <string> polyLines3;
	vector <string> polyLines4;
	vector <string> polyLines5;
	vector <string> polyLines6;
	vector <string> polyLines7;
	vector <string> polyLines8;
	vector<Polygon*> polygons;
	vector<Polygon*> updatedPolygons;
	vector<int> vertices;
	vector<int> vertices2;
	vector<int> vertices3;
	vector<int> vertices4;
	vector<int> vertices5;
	vector<int> vertices6;
	vector<int> vertices7;
	vector<int> vertices8;
	vector<string> clippingEdges;
	vector<Vertice*> polygonVertice;
	vector<Vertice*> polygonVertice2;
	vector<Vertice*> polygonVertice3;
	vector<Vertice*> polygonVertice4;
	vector<Vertice*> polygonVertice5;
	vector<Vertice*> polygonVertice6;
	vector<Vertice*> polygonVertice7;
	vector<Vertice*> polygonVertice8;
	vector<Vertice*>finalVertices;


	float scaleFactor = 1.0;
	float rotationFactor = 0;
	float xTranslationFactor = 0;
	float yTranslationFactor = 0;
	int lowerXBoundaryWW;
	int lowerYBoundaryWW;
	int upperXBoundaryWW;
	int upperYBoundaryWW;


	//clipping edges
	clippingEdges.push_back("right");
	clippingEdges.push_back("left");
	clippingEdges.push_back("top");
	clippingEdges.push_back("bottom");

	for (int i = 1; i < argc; i++ ){
		
		if (strcmp(argv[i], "-f") == 0) {
			inFile = argv[i + 1];
			fileName = argv[i + 1];
		}

		if (strcmp(argv[i], "-s") == 0) {
			scaleFactor = atof(argv[i + 1]);
		}


		if (strcmp(argv[i], "-r") == 0) {
			rotationFactor = atof(argv[i + 1]);
		}

		if (strcmp(argv[i], "-m") == 0) {
			xTranslationFactor = atof(argv[i + 1]);
			
		}

		if (strcmp(argv[i], "-n") == 0) {
			yTranslationFactor = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-a") == 0) {
			lowerXBoundaryWW = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-b") == 0) {
			lowerYBoundaryWW = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-c") == 0) {
			upperXBoundaryWW = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-d") == 0) {
			upperYBoundaryWW = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-j") == 0) {
			
		}
		if (strcmp(argv[i], "-k") == 0) {
			
		}
		if (strcmp(argv[i], "-o") == 0) {
			
		}

		if (strcmp(argv[i], "-p") == 0) {
			
		}


	}

	if (argc <= 1) {
		inFile = "hw4_1.ps";
		fileName = "hw4_1.ps";
	}

	ifstream File(inFile.c_str());
	getline(File, line);


	//initial file
	ofstream myfile("example.xpm");

	////cout << inFile;

	xpm.push_back("/* XPM */\n"); 
	xpm.push_back("static char *sco100[] = {\n");
	xpm.push_back("/* width height num_colors chars_per_pixel */\n");
	xpm.push_back("\"500 500 2 1\",\n");
	xpm.push_back("/* colors */\n");
	xpm.push_back("\"X c #010101\",\n");
	xpm.push_back("\"-  c #ffffff\",\n");
	xpm.push_back("/* pixels */\n");

	//position 8 is beginning

	string whiteBackground(500, '-'); 
	
	//creatingwhitespace
	int k = 0;
	while(k < 500){
		if (k != 499) {
			xpm.push_back("\"" + whiteBackground + "\",\n");
			k++;
		}

		if (k == 499) {
			xpm.push_back("\"" + whiteBackground + "\"\n");
			k++;
		}

	}	
	xpm.push_back("};");

	//reads file



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//for polygons
	if (fileName[2] == '3' || fileName[2] == '4' || fileName[2] == '5') {

		

		vector<int> outputVertices;


		while (!File.eof() && line != "stroke") {
			getline(File, line);

			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines.push_back(line);
			}
		}


		getline(File, line);

		while (!File.eof() && line != "stroke") {
			getline(File, line);
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines2.push_back(line);
			}

		}

		getline(File, line);

		while (!File.eof() && line != "stroke") {
			getline(File, line);
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines3.push_back(line);
			}

		}

		getline(File, line);

		while (!File.eof() && line != "stroke") {
			getline(File, line);
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines4.push_back(line);
			}

		}
		//getline(File, line);

		while (!File.eof() && line != "stroke") {
			getline(File, line);
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines4.push_back(line);
			}


		}

		getline(File, line);

		while (!File.eof() && line != "stroke") {
			getline(File, line);
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines5.push_back(line);
			}

		}
		getline(File, line);

		while (!File.eof() && line != "stroke") {
			getline(File, line);
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines6.push_back(line);
			}

		}

		getline(File, line);

		while (!File.eof() && line != "stroke") {
			getline(File, line);
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines7.push_back(line);
			}

		}

		getline(File, line);

		while (!File.eof() && line != "stroke") {
			getline(File, line);
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {
				istringstream iss(line);
				for (string line; iss >> line; )
					polyLines8.push_back(line);
			}

		}

		int i = 0;
		while (i < polyLines.size() - 4) {
			Line* newLine = new Line(atoi(polyLines[i].c_str()), atoi(polyLines[i + 1].c_str()), atoi(polyLines[i + 3].c_str()), atoi(polyLines[i + 4].c_str()));
			storage.push_back(newLine);
			i += 3;

		}

		//polygon 2
		if (polyLines2.size() != 0) {
			int i = 0;
			while (i < polyLines2.size() - 4) {
				Line* newLine = new Line(atoi(polyLines2[i].c_str()), atoi(polyLines2[i + 1].c_str()), atoi(polyLines2[i + 3].c_str()), atoi(polyLines2[i + 4].c_str()));
				storage2.push_back(newLine);
				i += 3;

			}


			int x1 = storage2[storage2.size() - 1]->x2;
			int y1 = storage2[storage2.size() - 1]->y2;

			int x2 = storage2[0]->x1;
			int y2 = storage2[0]->y1;
			Line* newLine2 = new Line(x1, y1, x2, y2);

			storage2.insert(storage2.begin(), newLine2);

			Polygon* newPolygon2 = new Polygon(storage2);
			newPolygon2 = scalePolygon(newPolygon2, scaleFactor);
			newPolygon2 = rotatePolygon(newPolygon2, rotationFactor);
			newPolygon2 = xTranslatePolygon(newPolygon2, xTranslationFactor);
			newPolygon2 = yTranslatePolygon(newPolygon2, yTranslationFactor);


			//polygons.push_back(newPolygon2);
			//cout << "newPolygon2" << endl;
			for (int i = 0; i < newPolygon2->polyLines.size(); i++) {
				//cout << newPolygon2->polyLines[i]->x1 << " " << newPolygon2->polyLines[i]->y1 << " " << newPolygon2->polyLines[i]->x2 << " " << newPolygon2->polyLines[i]->y2 << endl;
			}
			vertices2.push_back(newPolygon2->polyLines[0]->x1);
			vertices2.push_back(newPolygon2->polyLines[0]->y1);
			vertices2.push_back(newPolygon2->polyLines[0]->x2);
			vertices2.push_back(newPolygon2->polyLines[0]->y2);

			//cout << "Current Polygon size is " << polygons.size() << endl;
			//cout << "This is polygon 2" << endl;

			for (int i = 1; i < newPolygon2->polyLines.size(); i++) {
				vertices.push_back(newPolygon2->polyLines[i]->x2);
				vertices.push_back(newPolygon2->polyLines[i]->y2);
			}

			for (int i = 0; i < vertices2.size(); i += 2) {


				Vertice* newVertice = new Vertice(vertices2[i], vertices2[i + 1]);
				polygonVertice2.push_back(newVertice);
			}

			int counter = 0;
			for (int i = 0; i < storage2.size(); i++) {
				bool temp = isFullyInside(newPolygon2->polyLines[i]);
				if (temp == true) {
					counter++;
				}
			}
			if (counter != 0) {
				polygons.push_back(newPolygon2);
			}
			if (counter == 0) {
				//cout << "Polygon is fully outside of clipping area." << endl;
			}

			

			

			//checking to see if fully inside or outside
			else if (counter == storage2.size()) {
				vector<string> newXPM2 = xpm;
				xpm = printXPM(newPolygon2, newXPM2);

				vector<string> filledXPM2 = xpm;
				xpm = fillPolygon(newPolygon2, filledXPM2);
			}

			


		}

		//polygon 3
		if (polyLines3.size() != 0) {
			int i = 0;
			while (i < polyLines3.size() - 4) {
				Line* newLine = new Line(atoi(polyLines3[i].c_str()), atoi(polyLines3[i + 1].c_str()), atoi(polyLines3[i + 3].c_str()), atoi(polyLines3[i + 4].c_str()));
				storage3.push_back(newLine);
				i += 3;

			}


			int x1 = storage3[storage3.size() - 1]->x2;
			int y1 = storage3[storage3.size() - 1]->y2;

			int x2 = storage3[0]->x1;
			int y2 = storage3[0]->y1;
			Line* newLine2 = new Line(x1, y1, x2, y2);

			storage3.insert(storage3.begin(), newLine2);


			Polygon* newPolygon3 = new Polygon(storage3);
			newPolygon3 = scalePolygon(newPolygon3, scaleFactor);
			newPolygon3 = rotatePolygon(newPolygon3, rotationFactor);
			newPolygon3 = xTranslatePolygon(newPolygon3, xTranslationFactor);
			newPolygon3 = yTranslatePolygon(newPolygon3, yTranslationFactor);

			//polygons.push_back(newPolygon3);
			//cout << "newPolygon3" << endl;
			for (int i = 0; i < newPolygon3->polyLines.size(); i++) {
				//cout << newPolygon3->polyLines[i]->x1 << " " << newPolygon3->polyLines[i]->y1 << " " << newPolygon3->polyLines[i]->x2 << " " << newPolygon3->polyLines[i]->y2 << endl;
			}
			vertices3.push_back(newPolygon3->polyLines[0]->x1);
			vertices3.push_back(newPolygon3->polyLines[0]->y1);
			vertices3.push_back(newPolygon3->polyLines[0]->x2);
			vertices3.push_back(newPolygon3->polyLines[0]->y2);


			//cout << "Current Polygon size is " << polygons.size() << endl;
			//	cout << "This is polygon 3" << endl;

			for (int i = 1; i < newPolygon3->polyLines.size(); i++) {
				vertices3.push_back(newPolygon3->polyLines[i]->x2);
				vertices3.push_back(newPolygon3->polyLines[i]->y2);
			}

			for (int i = 0; i < vertices3.size(); i += 2) {


				Vertice* newVertice = new Vertice(vertices3[i], vertices3[i + 1]);
				polygonVertice3.push_back(newVertice);

			}

			int counter = 0;
			for (int i = 0; i < storage3.size(); i++) {
				bool temp = isFullyInside(newPolygon3->polyLines[i]);
				if (temp == true) {
					counter++;
				}
			}
			if (counter != 0) {
				polygons.push_back(newPolygon3);
			}
			if (counter == 0) {
				//cout << "Polygon is fully outside of clipping area." << endl;
			}

			//checking to see if fully inside or outside
			else if (counter == storage3.size()) {
				vector<string> newXPM2 = xpm;
				xpm = printXPM(newPolygon3, newXPM2);

				vector<string> filledXPM2 = xpm;
				xpm = fillPolygon(newPolygon3, filledXPM2);
			}

		}


		
		//polygon 4
		if (polyLines4.size() != 0) {
			int i = 0;
			while (i < polyLines4.size() - 4) {
				Line* newLine = new Line(atoi(polyLines4[i].c_str()), atoi(polyLines4[i + 1].c_str()), atoi(polyLines4[i + 3].c_str()), atoi(polyLines4[i + 4].c_str()));
				storage4.push_back(newLine);
				i += 3;

			}


			int x1 = storage4[storage4.size() - 1]->x2;
			int y1 = storage4[storage4.size() - 1]->y2;

			int x2 = storage4[0]->x1;
			int y2 = storage4[0]->y1;
			Line* newLine2 = new Line(x1, y1, x2, y2);

			storage4.insert(storage4.begin(), newLine2);


			Polygon* newPolygon4 = new Polygon(storage4);
			newPolygon4 = scalePolygon(newPolygon4, scaleFactor);
			newPolygon4 = rotatePolygon(newPolygon4, rotationFactor);
			newPolygon4 = xTranslatePolygon(newPolygon4, xTranslationFactor);
			newPolygon4 = yTranslatePolygon(newPolygon4, yTranslationFactor);
			//polygons.push_back(newPolygon4);
			//cout << "newPolygon4" << endl;
			for (int i = 0; i < newPolygon4->polyLines.size(); i++) {
				//cout << newPolygon4->polyLines[i]->x1 << " " << newPolygon4 ->polyLines[i]->y1 << " " << newPolygon4->polyLines[i]->x2 << " " << newPolygon4->polyLines[i]->y2 << endl;
			}
			vertices4.push_back(newPolygon4->polyLines[0]->x1);
			vertices4.push_back(newPolygon4->polyLines[0]->y1);
			vertices4.push_back(newPolygon4->polyLines[0]->x2);
			vertices4.push_back(newPolygon4->polyLines[0]->y2);

			//cout << "Current Polygon size is " << polygons.size() << endl;
			//cout << "This is polygon 4" << endl;

			for (int i = 1; i < newPolygon4->polyLines.size(); i++) {
				vertices4.push_back(newPolygon4->polyLines[i]->x2);
				vertices4.push_back(newPolygon4->polyLines[i]->y2);
			}

			for (int i = 0; i < vertices4.size(); i += 2) {


				Vertice* newVertice = new Vertice(vertices4[i], vertices4[i + 1]);
				polygonVertice4.push_back(newVertice);

			}

			int counter = 0;
			for (int i = 0; i < storage4.size(); i++) {
				bool temp = isFullyInside(newPolygon4->polyLines[i]);
				if (temp == true) {
					counter++;
				}
			}
			if (counter != 0) {
				polygons.push_back(newPolygon4);
			}
			if (counter == 0) {
				//cout << "Polygon is fully outside of clipping area." << endl;
			}

			//checking to see if fully inside or outside
			else if (counter == storage4.size()) {
				vector<string> newXPM2 = xpm;
				xpm = printXPM(newPolygon4, newXPM2);

				vector<string> filledXPM2 = xpm;
				xpm = fillPolygon(newPolygon4, filledXPM2);
			}

		}

		

		
		
		
		//polygon 5
		
		if (polyLines5.size() != 0) {
			int i = 0;
			while (i < polyLines5.size() - 4) {
				Line* newLine = new Line(atoi(polyLines5[i].c_str()), atoi(polyLines5[i + 1].c_str()), atoi(polyLines5[i + 3].c_str()), atoi(polyLines5[i + 4].c_str()));
				storage5.push_back(newLine);
				i += 3;

			}


			int x1 = storage5[storage5.size() - 1]->x2;
			int y1 = storage5[storage5.size() - 1]->y2;

			int x2 = storage5[0]->x1;
			int y2 = storage5[0]->y1;
			Line* newLine2 = new Line(x1, y1, x2, y2);

			storage5.insert(storage5.begin(), newLine2);


			Polygon* newPolygon5 = new Polygon(storage5);
			newPolygon5 = scalePolygon(newPolygon5, scaleFactor);
			newPolygon5 = rotatePolygon(newPolygon5, rotationFactor);
			newPolygon5 = xTranslatePolygon(newPolygon5, xTranslationFactor);
			newPolygon5 = yTranslatePolygon(newPolygon5, yTranslationFactor);
			//polygons.push_back(newPolygon5);
			//cout << "newPolygon5" << endl;
			for (int i = 0; i < newPolygon5->polyLines.size(); i++) {
				//cout << newPolygon5->polyLines[i]->x1 << " " << newPolygon5->polyLines[i]->y1 << " " << newPolygon5->polyLines[i]->x2 << " " << newPolygon5->polyLines[i]->y2 << endl;
			}
			vertices5.push_back(newPolygon5->polyLines[0]->x1);
			vertices5.push_back(newPolygon5->polyLines[0]->y1);
			vertices5.push_back(newPolygon5->polyLines[0]->x2);
			vertices5.push_back(newPolygon5->polyLines[0]->y2);

			//cout << "Current Polygon size is " << polygons.size() << endl;
			//cout << "This is polygon 5" << endl;

			for (int i = 1; i < newPolygon5->polyLines.size(); i++) {
				vertices5.push_back(newPolygon5->polyLines[i]->x2);
				vertices5.push_back(newPolygon5->polyLines[i]->y2);
			}

			for (int i = 0; i < vertices5.size(); i += 2) {


				Vertice* newVertice = new Vertice(vertices5[i], vertices5[i + 1]);
				polygonVertice5.push_back(newVertice);

			}

			int counter = 0;
			for (int i = 0; i < storage5.size(); i++) {
				bool temp = isFullyInside(newPolygon5->polyLines[i]);
				if (temp == true) {
					counter++;
				}
			}
			if (counter != 0) {
				polygons.push_back(newPolygon5);
			}
			if (counter == 0) {
				//cout << "Polygon is fully outside of clipping area." << endl;
			}

			//checking to see if fully inside or outside
			else if (counter == storage5.size()) {
				vector<string> newXPM2 = xpm;
				xpm = printXPM(newPolygon5, newXPM2);

				vector<string> filledXPM2 = xpm;
				xpm = fillPolygon(newPolygon5, filledXPM2);
			}

		}

		//polygon 6

		if (polyLines6.size() != 0) {
			int i = 0;
			while (i < polyLines6.size() - 4) {
				Line* newLine = new Line(atoi(polyLines6[i].c_str()), atoi(polyLines6[i + 1].c_str()), atoi(polyLines6[i + 3].c_str()), atoi(polyLines6[i + 4].c_str()));
				storage6.push_back(newLine);
				i += 3;

			}


			int x1 = storage6[storage6.size() - 1]->x2;
			int y1 = storage6[storage6.size() - 1]->y2;

			int x2 = storage6[0]->x1;
			int y2 = storage6[0]->y1;
			Line* newLine2 = new Line(x1, y1, x2, y2);

			storage6.insert(storage6.begin(), newLine2);


			Polygon* newPolygon6 = new Polygon(storage6);
			newPolygon6 = scalePolygon(newPolygon6, scaleFactor);
			newPolygon6 = rotatePolygon(newPolygon6, rotationFactor);
			newPolygon6 = xTranslatePolygon(newPolygon6, xTranslationFactor);
			newPolygon6 = yTranslatePolygon(newPolygon6, yTranslationFactor);
			//polygons.push_back(newPolygon6);

			//cout << "newPolygon6" << endl;
			for (int i = 0; i < newPolygon6->polyLines.size(); i++) {
				//cout << newPolygon6->polyLines[i]->x1 << " " << newPolygon6->polyLines[i]->y1 << " " << newPolygon6->polyLines[i]->x2 << " " << newPolygon6->polyLines[i]->y2 << endl;
			}
			vertices6.push_back(newPolygon6->polyLines[0]->x1);
			vertices6.push_back(newPolygon6->polyLines[0]->y1);
			vertices6.push_back(newPolygon6->polyLines[0]->x2);
			vertices6.push_back(newPolygon6->polyLines[0]->y2);

			//cout << "Current Polygon size is " << polygons.size() << endl;
			//cout << "This is polygon 6" << endl;

			for (int i = 1; i < newPolygon6->polyLines.size(); i++) {
				vertices6.push_back(newPolygon6->polyLines[i]->x2);
				vertices6.push_back(newPolygon6->polyLines[i]->y2);
			}

			for (int i = 0; i < vertices6.size(); i += 2) {


				Vertice* newVertice = new Vertice(vertices6[i], vertices6[i + 1]);
				polygonVertice6.push_back(newVertice);

			}

			int counter = 0;
			for (int i = 0; i < storage6.size(); i++) {
				bool temp = isFullyInside(newPolygon6->polyLines[i]);
				if (temp == true) {
					counter++;
				}
			}
			if (counter != 0) {
				polygons.push_back(newPolygon6);
			}
			if (counter == 0) {
				//cout << "Polygon is fully outside of clipping area." << endl;
			}

			//checking to see if fully inside or outside
			else if (counter == storage6.size()) {
				vector<string> newXPM2 = xpm;
				xpm = printXPM(newPolygon6, newXPM2);

				vector<string> filledXPM2 = xpm;
				xpm = fillPolygon(newPolygon6, filledXPM2);
			}

		}

		//polygon 7

		if (polyLines7.size() != 0) {
			int i = 0;
			while (i < polyLines7.size() - 4) {
				Line* newLine = new Line(atoi(polyLines7[i].c_str()), atoi(polyLines7[i + 1].c_str()), atoi(polyLines7[i + 3].c_str()), atoi(polyLines7[i + 4].c_str()));
				storage7.push_back(newLine);
				i += 3;

			}


			int x1 = storage7[storage7.size() - 1]->x2;
			int y1 = storage7[storage7.size() - 1]->y2;

			int x2 = storage7[0]->x1;
			int y2 = storage7[0]->y1;
			Line* newLine2 = new Line(x1, y1, x2, y2);

			storage7.insert(storage7.begin(), newLine2);


			Polygon* newPolygon7 = new Polygon(storage7);
			newPolygon7 = scalePolygon(newPolygon7, scaleFactor);
			newPolygon7 = rotatePolygon(newPolygon7, rotationFactor);
			newPolygon7 = xTranslatePolygon(newPolygon7, xTranslationFactor);
			newPolygon7 = yTranslatePolygon(newPolygon7, yTranslationFactor);
			//polygons.push_back(newPolygon7);

			//cout << "newPolygon7" << endl;
			for (int i = 0; i < newPolygon7->polyLines.size(); i++) {
				//cout << newPolygon7->polyLines[i]->x1 << " " << newPolygon7->polyLines[i]->y1 << " " << newPolygon7->polyLines[i]->x2 << " " << newPolygon7->polyLines[i]->y2 << endl;
			}
			vertices7.push_back(newPolygon7->polyLines[0]->x1);
			vertices7.push_back(newPolygon7->polyLines[0]->y1);
			vertices7.push_back(newPolygon7->polyLines[0]->x2);
			vertices7.push_back(newPolygon7->polyLines[0]->y2);

			//cout << "Current Polygon size is " << polygons.size() << endl;
			//cout << "This is polygon 7" << endl;

			for (int i = 1; i < newPolygon7->polyLines.size(); i++) {
				vertices7.push_back(newPolygon7->polyLines[i]->x2);
				vertices7.push_back(newPolygon7->polyLines[i]->y2);
			}

			for (int i = 0; i < vertices7.size(); i += 2) {


				Vertice* newVertice = new Vertice(vertices7[i], vertices7[i + 1]);
				polygonVertice7.push_back(newVertice);

			}

			int counter = 0;
			for (int i = 0; i < storage7.size(); i++) {
				bool temp = isFullyInside(newPolygon7->polyLines[i]);
				if (temp == true) {
					counter++;
				}
			}
			if (counter != 0) {
				polygons.push_back(newPolygon7);
			}
			if (counter == 0) {
				//cout << "Polygon is fully outside of clipping area." << endl;
			}

			//checking to see if fully inside or outside
			else if (counter == storage7.size()) {
				vector<string> newXPM2 = xpm;
				xpm = printXPM(newPolygon7, newXPM2);

				vector<string> filledXPM2 = xpm;
				xpm = fillPolygon(newPolygon7, filledXPM2);

				
			}

		}
		
		//polygon 8
		if (polyLines8.size() != 0) {
			int i = 0;
			while (i < polyLines8.size() - 4) {
				Line* newLine = new Line(atoi(polyLines8[i].c_str()), atoi(polyLines8[i + 1].c_str()), atoi(polyLines8[i + 3].c_str()), atoi(polyLines8[i + 4].c_str()));
				storage8.push_back(newLine);
				i += 3;

			}


			int x1 = storage8[storage8.size() - 1]->x2;
			int y1 = storage8[storage8.size() - 1]->y2;

			int x2 = storage8[0]->x1;
			int y2 = storage8[0]->y1;
			Line* newLine2 = new Line(x1, y1, x2, y2);

			storage8.insert(storage8.begin(), newLine2);


			Polygon* newPolygon8 = new Polygon(storage8);
			newPolygon8 = scalePolygon(newPolygon8, scaleFactor);
			newPolygon8 = rotatePolygon(newPolygon8, rotationFactor);
			newPolygon8 = xTranslatePolygon(newPolygon8, xTranslationFactor);
			newPolygon8 = yTranslatePolygon(newPolygon8, yTranslationFactor);

			//cout << "newPolygon8" << endl;
			for (int i = 0; i < newPolygon8->polyLines.size(); i++) {
				//cout << newPolygon8->polyLines[i]->x1 << " " << newPolygon8->polyLines[i]->y1 << " " << newPolygon8->polyLines[i]->x2 << " " << newPolygon8->polyLines[i]->y2 << endl;
			}
			//polygons.push_back(newPolygon8);
			vertices8.push_back(newPolygon8->polyLines[0]->x1);
			vertices8.push_back(newPolygon8->polyLines[0]->y1);
			vertices8.push_back(newPolygon8->polyLines[0]->x2);
			vertices8.push_back(newPolygon8->polyLines[0]->y2);

			//cout << "Current Polygon size is " << polygons.size() << endl;
			//cout << "This is polygon 8" << endl;

			for (int i = 1; i < newPolygon8->polyLines.size(); i++) {
				vertices8.push_back(newPolygon8->polyLines[i]->x2);
				vertices8.push_back(newPolygon8->polyLines[i]->y2);
			}

			for (int i = 0; i < vertices8.size(); i += 2) {


				Vertice* newVertice = new Vertice(vertices8[i], vertices8[i + 1]);
				polygonVertice8.push_back(newVertice);

			}

			int counter = 0;
			for (int i = 0; i < storage8.size(); i++) {
				bool temp = isFullyInside(newPolygon8->polyLines[i]);
				if (temp == true) {
					counter++;
				}
			}
			if (counter != 0) {
				polygons.push_back(newPolygon8);
			}
			if (counter == 0) {
				//cout << "Polygon is fully outside of clipping area." << endl;
			}

			//checking to see if fully inside or outside
			else if (counter == storage8.size()) {
				
				vector<string> newXPM2 = xpm;
				xpm = printXPM(newPolygon8, newXPM2);

				vector<string> filledXPM2 = xpm;
				xpm = fillPolygon(newPolygon8, filledXPM2);
			}

		}

	




		/////////////////////////////////////////////////////////////////////////////////////
		Polygon* newPolygon = new Polygon(storage);
		newPolygon = scalePolygon(newPolygon, scaleFactor);
		newPolygon = rotatePolygon(newPolygon, rotationFactor);
		newPolygon = xTranslatePolygon(newPolygon, xTranslationFactor);
		newPolygon = yTranslatePolygon(newPolygon, yTranslationFactor);
		//polygons.push_back(newPolygon);

	//	cout << "newPolygon" << endl;
		for (int i = 0; i < newPolygon->polyLines.size(); i++) {
			//cout << newPolygon->polyLines[i]->x1 << " " << newPolygon->polyLines[i]->y1 << " " << newPolygon->polyLines[i]->x2 << " " << newPolygon->polyLines[i]->y2 << endl;
		}

		vertices.push_back(newPolygon->polyLines[0]->x1);
		vertices.push_back(newPolygon->polyLines[0]->y1);
		vertices.push_back(newPolygon->polyLines[0]->x2);
		vertices.push_back(newPolygon->polyLines[0]->y2);


		//cout << "Current Polygon size is " << polygons.size() << endl;
		//cout << "This is polygon 0" << endl;

		for (int i = 1; i < newPolygon->polyLines.size(); i++) {
			vertices.push_back(newPolygon->polyLines[i]->x2);
			vertices.push_back(newPolygon->polyLines[i]->y2);
		}

		for (int i = 0; i < vertices.size(); i += 2) {


			Vertice* newVertice = new Vertice(vertices[i], vertices[i + 1]);
			polygonVertice.push_back(newVertice);

		}


		int counter = 0;
		for (int i = 0; i < storage.size(); i++) {
			bool temp = isFullyInside(newPolygon->polyLines[i]);
			if (temp == true) {
				counter++;
			}
		}
	
		if (counter != 0) {
			polygons.push_back(newPolygon);
		}
		if (counter == 0) {
			//cout << "Polygon is fully outside of clipping area." << endl;
		}

		//drawing for polygon if fully inside
		else if (counter == storage.size()) {
		
			vector<string> newXPM = xpm;
			xpm = printXPM(newPolygon, newXPM);

			vector<string> filledXPM = xpm;
			xpm = fillPolygon(newPolygon, filledXPM);

			
		}


		

		//Our new algorithm to clip polygons
		else {
			



		


		//	cout << "Polygon 0" << endl;
		
			for (int i = 0; i < polygons.size(); i++) {
				//cout << "Current Polygon Getting Clipped" << endl;
				//for (int i = 0; i < polygons[i]->polyLines.size(); i++) {
					//cout << polygons[i]->polyLines[i]->x1 << " " << polygons[i]->polyLines[i]->y1 << " " << polygons[i]->polyLines[i]->x2 << " " << polygons[i]->polyLines[i]->y2 << " " << endl;
				//}

				vector<int> vertices;
				vector<Vertice*> polygonVertice;

				vertices.push_back(polygons[i]->polyLines[0]->x1);
				vertices.push_back(polygons[i]->polyLines[0]->y1);
				vertices.push_back(polygons[i]->polyLines[0]->x2);
				vertices.push_back(polygons[i]->polyLines[0]->y2);

				for (int j = 1; j < polygons[i]->polyLines.size(); j++) {
					vertices.push_back(polygons[i]->polyLines[j]->x2);
					vertices.push_back(polygons[i]->polyLines[j]->y2);
				}


				
				for (int l = 0; l < vertices.size(); l += 2) {


					Vertice* newVertice = new Vertice(vertices[l], vertices[l + 1]);
					polygonVertice.push_back(newVertice);

				}

				




				polygons[i]->verticeList = polygonVertice;

				//cout << "Polygon " << i << endl;
				for (int k = 0; k < polygons[i]->polyLines.size(); k++) {
					//cout << polygons[i]->polyLines[k]->x1 << " " << polygons[i]->polyLines[k]->y1 << " " << polygons[i]->polyLines[k]->x2 << " " << polygons[i]->polyLines[k]->y2 << endl;

				}
			}

			Vertice* rightClipVertice1 = new Vertice(500, -1000);
			Vertice* rightClipVertice2 = new Vertice(500, 1000);

			Vertice* leftClipVertice1 = new Vertice(0, -1000);
			Vertice* leftClipVertice2 = new Vertice(0, 1000);

			Vertice* topClipVertice1 = new Vertice(-1000, 500);
			Vertice* topClipVertice2 = new Vertice(1000, 500);

			Vertice* bottomClipVertice1 = new Vertice(-1000, 0);
			Vertice* bottomClipVertice2 = new Vertice(1000, 0);

			for (int i = 0; i < polygons.size(); i++) {
				Polygon* p = polygons[i];

				vector<Vertice*>outputVertices = polygons[i]->verticeList;

				//FOR EACH CLIPPING EDGE (4 OF THEM)
				for (int k = 0; k < clippingEdges.size(); k++) {
					


						vector<Vertice*>outputVertices;
						//cout << "POLYGON LIST FOR NEXT EDGE CHECK" << endl;


						for (int j = 0; j < polygons[i]->verticeList.size() - 1; j++) {

							//cout << polygons[i]->verticeList[j]->xCoord << " " << polygons[i]->verticeList[j]->yCoord << endl;
						}


						if (isPointInside(polygons[i]->verticeList[0]->xCoord, polygons[i]->verticeList[0]->yCoord)) {
							//cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
							//cout << "INSIDE X VALUE IS " << polygons[i]->verticeList[0]->xCoord << " " << polygons[i]->verticeList[0]->yCoord << endl;
							outputVertices.push_back(polygons[i]->verticeList[0]);
						}

						//FOR EACH Vertice
						for (int j = 0; j < polygons[i]->verticeList.size() - 1; j++) {

							//cout << "output vertices" << endl;
							for (int k = 0; k < outputVertices.size(); k++) {

								//cout << outputVertices[k]->xCoord << " " << outputVertices[k]->yCoord << endl;
							}


							//cout << "test";
							//cout << "---------------------------------------------------------------------------------------------" << endl;
							//cout << "Current Vertice = " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;



							if (clippingEdges[k] == "right") {


								//cout << "Clipping against right boundary" << endl;
								//inside-inside
								if (polygons[i]->verticeList[j]->xCoord <= 500 && polygons[i]->verticeList[j + 1]->xCoord <= 500) {
									//cout << "Inside - Inside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									outputVertices.push_back(polygons[i]->verticeList[j + 1]);
								}

								//outside-outside
								if (polygons[i]->verticeList[j]->xCoord > 500 && polygons[i]->verticeList[j + 1]->xCoord > 500) {
									//cout << "Outside-Outside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									//cout << "Both Vertices Outside" << endl;
								}

								//inside-outside
								if (polygons[i]->verticeList[j]->xCoord <= 500 && polygons[i]->verticeList[j + 1]->xCoord > 500) {
									////cout << "Inside - Outside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									Vertice* intersectionVertice = intersectionOfPoints(polygons[i]->verticeList[j], polygons[i]->verticeList[j + 1], rightClipVertice1, rightClipVertice2);
									outputVertices.push_back(intersectionVertice);
								}


								//outside-inside
								if (polygons[i]->verticeList[j]->xCoord > 500 && polygons[i]->verticeList[j + 1]->xCoord <= 500) {
									//cout << "Outside - Inside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;

									Vertice* intersectionVertice = intersectionOfPoints(polygons[i]->verticeList[j], polygons[i]->verticeList[j + 1], rightClipVertice1, rightClipVertice2);
									outputVertices.push_back(intersectionVertice);
									outputVertices.push_back(polygons[i]->verticeList[j + 1]);
								}

							}
							if (clippingEdges[k] == "left") {
								//cout << "Clipping against left boundary" << endl;
								//inside-inside
								if (polygons[i]->verticeList[j]->xCoord >= 0 && polygons[i]->verticeList[j + 1]->xCoord >= 0) {
									//cout << "Inside - Inside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									outputVertices.push_back(polygons[i]->verticeList[j + 1]);
								}

								//outside-outside
								if (polygons[i]->verticeList[j]->xCoord < 0 && polygons[i]->verticeList[j + 1]->xCoord < 0) {
									//cout << "Outside-Outside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									//cout << "Both Vertices Outside" << endl;
								}

								//inside-outside
								if (polygons[i]->verticeList[j]->xCoord >= 0 && polygons[i]->verticeList[j + 1]->xCoord < 0) {
									//cout << "Inside - Outside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									Vertice* intersectionVertice = intersectionOfPoints(polygons[i]->verticeList[j], polygons[i]->verticeList[j + 1], leftClipVertice1, leftClipVertice2);
									outputVertices.push_back(intersectionVertice);
								}


								//outside-inside
								if (polygons[i]->verticeList[j]->xCoord < 0 && polygons[i]->verticeList[j + 1]->xCoord >= 0) {
									//cout << "Outside - Inside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									Vertice* intersectionVertice = intersectionOfPoints(polygons[i]->verticeList[j], polygons[i]->verticeList[j + 1], leftClipVertice1, leftClipVertice2);
									outputVertices.push_back(intersectionVertice);
									outputVertices.push_back(polygons[i]->verticeList[j + 1]);
								}

							}

							if (clippingEdges[k] == "top") {
								//cout << "Clipping against top boundary" << endl;
								//inside-inside
								if (polygons[i]->verticeList[j]->yCoord <= 500 && polygons[i]->verticeList[j + 1]->yCoord <= 500) {
									//cout << "Inside - Inside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									outputVertices.push_back(polygons[i]->verticeList[j + 1]);
								}

								//outside-outside
								if (polygons[i]->verticeList[j]->yCoord > 500 && polygons[i]->verticeList[j + 1]->yCoord > 500) {
									//cout << "Outside-Outside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									//cout << "Both Vertices Outside" << endl;
								}

								//inside-outside
								if (polygons[i]->verticeList[j]->yCoord <= 500 && polygons[i]->verticeList[j + 1]->yCoord > 500) {
									//cout << "Inside - Outside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									Vertice* intersectionVertice = intersectionOfPoints(polygons[i]->verticeList[j], polygons[i]->verticeList[j + 1], topClipVertice1, topClipVertice2);
									outputVertices.push_back(intersectionVertice);
								}


								//outside-inside
								if (polygons[i]->verticeList[j]->yCoord > 500 && polygons[i]->verticeList[j + 1]->yCoord <= 500) {
									//cout << "Outside - Inside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									Vertice* intersectionVertice = intersectionOfPoints(polygons[i]->verticeList[j], polygons[i]->verticeList[j + 1], topClipVertice1, topClipVertice2);
									outputVertices.push_back(intersectionVertice);
									outputVertices.push_back(polygons[i]->verticeList[j + 1]);
								}
							}
							if (clippingEdges[k] == "bottom") {
								//cout << "Clipping against bottom boundary" << endl;
								//inside-inside
								if (polygons[i]->verticeList[j]->yCoord >= 0 && polygons[i]->verticeList[j + 1]->yCoord >= 0) {
									//cout << "Inside - Inside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									outputVertices.push_back(polygons[i]->verticeList[j + 1]);
								}

								//outside-outside
								if (polygons[i]->verticeList[j]->yCoord < 0 && polygons[i]->verticeList[j + 1]->yCoord < 0) {
									//cout << "Outside-Outside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									//cout << "Both Vertices Outside" << endl;
								}

								//inside-outside
								if (polygons[i]->verticeList[j]->yCoord >= 0 && polygons[i]->verticeList[j + 1]->yCoord < 0) {
									//cout << "Inside - Outside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									Vertice* intersectionVertice = intersectionOfPoints(polygons[i]->verticeList[j], polygons[i]->verticeList[j + 1], bottomClipVertice1, bottomClipVertice2);
									outputVertices.push_back(intersectionVertice);
								}


								//outside-inside
								if (polygons[i]->verticeList[j]->yCoord < 0 && polygons[i]->verticeList[j + 1]->yCoord >= 0) {
									//cout << "Outside - Inside found for vertices  " << polygons[i]->verticeList[j]->xCoord << " , " << polygons[i]->verticeList[j]->yCoord << " | " << polygons[i]->verticeList[j + 1]->xCoord << " , " << polygons[i]->verticeList[j + 1]->yCoord << endl;
									Vertice* intersectionVertice = intersectionOfPoints(polygons[i]->verticeList[j], polygons[i]->verticeList[j + 1], bottomClipVertice1, bottomClipVertice2);
									outputVertices.push_back(intersectionVertice);
									outputVertices.push_back(polygons[i]->verticeList[j + 1]);
								}

							}

						}

						polygons[i]->verticeList = outputVertices;
						//cout << "Final = " << endl;
						for (int i = 0; i < outputVertices.size(); i++) {
							//cout << "(" << outputVertices[i]->xCoord << "," << outputVertices[i]->yCoord << ")" << endl;
						}
						finalVertices = outputVertices;






					}

					////cout << "XXX";
					for (int i = 0; i < finalVertices.size(); i++) {
						////cout << "X = " << finalVertices[i]->xCoord << " Y = " << finalVertices[i]->yCoord << endl;
					}
					vector<Line*> finalLines;

					for (int i = 0; i < finalVertices.size() - 1; i++) {
						int x1 = finalVertices[i]->xCoord;
						int y1 = finalVertices[i]->yCoord;
						int x2 = finalVertices[i + 1]->xCoord;
						int y2 = finalVertices[i + 1]->yCoord;

						if (x1 == 500) {
							x1 = 499;
						}

						if (x2 == 500) {
							x2 = 499;
						}

						if (y1 == 500) {
							y1 = 492;
						}

						if (y2 == 500) {
							y2 = 492;
						}
						Line* newLine = new Line(x1, y1, x2, y2);
						finalLines.push_back(newLine);
					}





					////cout << "These lines";
					for (int i = 0; i < finalLines.size(); i++) {
						////cout << finalLines[i]->x1 << "  " << finalLines[i]->y1 << "  " << finalLines[i]->x2 << " " << finalLines[i]->y2 << endl;
					}

					polygons[i]->polyLines = finalLines;

					////cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
					////cout << "Current Polygon to be printed = " << i << endl;
					Polygon* newPolygon = new Polygon(finalLines);
					vector<string> newXPM = xpm;
					xpm = printXPM(newPolygon, newXPM);

					////cout << "Just Printed" << endl;
					////cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

					vector<string> filledXPM = xpm;
					xpm = fillPolygon(newPolygon, filledXPM);

				
				}  //end of polygon for loop so draw inside here
			





		}
		//

		////cout << polygons.size() << endl;
		for (int i = 0; i < polygons.size(); i++) {
			////cout << "Polygon " << i << endl;

			for (int k = 0; k < polygons[i]->polyLines.size(); k++) {
				////cout << polygons[i]->polyLines[k]->x1 << " " << polygons[i]->polyLines[k]->y1 << " " << polygons[i]->polyLines[k]->x2 << " " << polygons[i]->polyLines[k]->y2 << endl;
			}
		}


	}
	

	else {
		while (!File.eof()) {

			//skips first two lines

			if (fileName[2] = 1) {
				getline(File, line);
			}
			else if (fileName[2] = 2) {
				getline(File, line);
			}
			//if valid file
			if (line != "" && line != "%%%BEGIN" && line != "%%%END") {


				//[poitcodes
				int point1Code;
				int point2Code;

				int resultAnd;
				int resultOr;

				vector<string> lines;
				istringstream iss(line);

				for (string line; iss >> line; )
					lines.push_back(line);

				////cout << "Current Line" << lines[0] + "  " << lines[1] << +" " << lines[2] + " " << lines[3] + " " << lines[4] + " " << endl;

				Line* newLine = new Line(atoi(lines[0].c_str()), atoi(lines[1].c_str()), atoi(lines[2].c_str()), atoi(lines[3].c_str()));
				newLine->printLineInfo();

				point1Code = pointCode1Giver(newLine);
				point2Code = pointCode2Giver(newLine);


				//checks pointcodes and compares bits to see location
				////cout << "Point 1 Code is = " << point1Code << endl;
				////cout << "Point 2 Code is = " << point2Code << endl;

				resultOr = point1Code | point2Code;
				resultAnd = point1Code & point2Code;

				////cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
				////cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside

				//std:://cout << std::bitset<4>(point1Code) << "\n";
				//std:://cout << std::bitset<4>(point2Code) << "\n";

				bitset<4> p1(point1Code);
				bitset<4> p2(point1Code);

				//draws points
				if (point1Code == 0) {
					string newPoint1 = xpm[500 - newLine->y1];
					newPoint1[newLine->x1 + 1] = 'X';
					xpm[508 - newLine->y1] = newPoint1;
				}

				if (point2Code == 0) {
					string newPoint2 = xpm[500 - newLine->y2];
					newPoint2[newLine->x2 + 1] = 'X';
					xpm[508 - newLine->y2] = newPoint2;
				}

				//if vert / horizontal line
				if (resultOr == 0) {
					if (newLine->y1 == newLine->y2) {
						if (newLine->x1 < newLine->x2) {
							for (int i = newLine->x1 + 1; i < newLine->x2 + 1; i++) {
								xpm[500 - newLine->y1][i] = 'X';
							}
						}

						else {
							for (int i = newLine->x2 + 1; i < newLine->x1 + 1; i++) {
								xpm[500 - newLine->y1][i] = 'X';
							}
						}
					}

					if (newLine->x1 == newLine->x2) {
						if (newLine->y1 < newLine->y2) {
							for (int i = 500 - newLine->y2; i < 500 - newLine->y1; i++) {
								xpm[i][newLine->x1 + 1] = 'X';
							}
						}
						else {
							for (int i = 500 - newLine->y2; i < 500 - newLine->y1; i++) {
								xpm[i][newLine->x1 + 1] = 'X';
							}
						}
					}

					//ddt for drawing
					float x1 = newLine->x1;
					float y1 = newLine->y1;
					int counter;

					if ((newLine->y2 - newLine->y1) >= (newLine->x2 - newLine->x1)) {
						counter = (newLine->y2 - newLine->y1);
					}

					else if ((newLine->y2 - newLine->y1) <= (newLine->x2 - newLine->x1)) {
						counter = (newLine->x2 - newLine->x1);
					}

					float yChange = (newLine->y2 - newLine->y1);
					float xChange = (newLine->x2 - newLine->x1);

					xChange = xChange / counter;
					yChange = yChange / counter;

					int i = 1;
					while (i < counter) {
						xpm[500 - y1][x1] = 'X';
						x1 = x1 + xChange;
						y1 = y1 + yChange;
						i++;
					}

				}

				//if outside view
				else if (resultAnd != 0) {
					////cout << "line not drawn" << endl;
				}


				//if inside
				//sorry this section is very messy
				else if (resultAnd == 0 && resultOr != 0) {

					bitset<4> temp1(point1Code);
					bitset<4> temp2(point2Code);

					string p1 = temp1.to_string();
					string p2 = temp2.to_string();

				//	//cout << "test222" << newLine->x1 << "  " << newLine->y1 << "   " << newLine->x2 << "  " << newLine->y2 << "  " << endl;
					double newX1 = newLine->x1;
					double newX2 = newLine->x2;
					double newY1 = newLine->y1;
					double newY2 = newLine->y2;

					double tempy1 = 1.0 * newLine->y1;
					double tempy2 = 1.0 * newLine->y2;
					double tempx1 = 1.0 * newLine->x1;
					double tempx2 = 1.0 * newLine->x2;

					////cout << "Original" << endl;
					////cout << "NewX1 = " << newX1 << endl;
					////cout << "NewY1 = " << newY1 << endl;
					////cout << "NewX2 = " << newX2 << endl;
					////cout << "NewY2 = " << newY2 << endl;

					for (int i = 0; i < 4; i++) {
						////cout << i << endl;


						//checks each point for a bit flop, acts accordingly
						if (i == 0) {
							if (p1[i] == '1') {
								////cout << "test222" << newLine->x1 << "  " << newLine->y1 << "   " << newLine->x2 << "  " << newLine->y2 << "  " << endl;

								newY1 = 500 * 1.0;
								newX1 = tempx1 - (tempy1 - newY1) / (tempy2 - tempy1) * (tempx2 - tempx1);

								////cout << "DETECTED P1[1] = 1" << endl;
								////cout << "NewX1 = " << newX1 << endl;
							//	//cout << "NewY1 = " << newY1 << endl;
							//	//cout << "NewX2 = " << newX2 << endl;
							//	//cout << "NewY2 = " << newY2 << endl;

								newLine->x1 = newX1;
								newLine->y1 = newY1;
								newLine->x2 = newX2;
								newLine->y2 = newY2;

								point1Code = pointCode1Giver(newLine);
								point2Code = pointCode2Giver(newLine);

								resultOr = point1Code | point2Code;
								resultAnd = point1Code & point2Code;

							//	//cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
							//	//cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside


								//std:://cout << std::bitset<4>(point1Code) << "\n";
								//std:://cout << std::bitset<4>(point2Code) << "\n";

								if (resultAnd != 0) {
								//	//cout << "Line is not on plane" << endl;
									break;
								}
								if (resultOr == 0) {
									////cout << "Completely Inside" << endl;
									break;
								}

							}

							if (p2[i] == '1') {
								newY2 = 500 * 1.0;
								newX2 = tempx2 - (tempy2 - newY2) / (tempy2 - tempy1) * (tempx2 - tempx1) + tempy1;
								////cout << "DETECTED P2[1] = 1" << endl;
								////cout << "NewX1 = " << newX1 << endl;
								////cout << "NewY1 = " << newY1 << endl;
								////cout << "NewX2 = " << newX2 << endl;
								////cout << "NewY2 = " << newY2 << endl;

								newLine->x1 = newX1;
								newLine->y1 = newY1;
								newLine->x2 = newX2;
								newLine->y2 = newY2;

								point1Code = pointCode1Giver(newLine);
								point2Code = pointCode2Giver(newLine);

								resultOr = point1Code | point2Code;
								resultAnd = point1Code & point2Code;

								////cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
								////cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside


								//std:://cout << std::bitset<4>(point1Code) << "\n";
								//std:://cout << std::bitset<4>(point2Code) << "\n";

								if (resultAnd != 0) {
									////cout << "Line is not on plane" << endl;
									break;
								}
								if (resultOr == 0) {
									////cout << "Completely Inside" << endl;
									break;
								}



							}

						}

						if (i == 1) {
							if (p1[i] == '1') {
								newY1 = 0 * 1.0;
								newX1 = (tempy2 - tempy1) / (tempx2 - tempx1) * (newX1 - tempx1) + tempy1;
								////cout << "DETECTED P1[1] = 1" << endl;
								////cout << "NewX1 = " << newX1 << endl;
								////cout << "NewY1 = " << newY1 << endl;
								////cout << "NewX2 = " << newX2 << endl;
								////cout << "NewY2 = " << newY2 << endl;

								newLine->x1 = newX1;
								newLine->y1 = newY1;
								newLine->x2 = newX2;
								newLine->y2 = newY2;

								point1Code = pointCode1Giver(newLine);
								point2Code = pointCode2Giver(newLine);

								resultOr = point1Code | point2Code;
								resultAnd = point1Code & point2Code;

								////cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
								////cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside


								//std:://cout << std::bitset<4>(point1Code) << "\n";
								//std:://cout << std::bitset<4>(point2Code) << "\n";

								if (resultAnd != 0) {
								//	//cout << "Line is not on plane" << endl;
									break;
								}
								if (resultOr == 0) {
								//	//cout << "Completely Inside" << endl;
									break;
								}


							}

							if (p2[i] == '1') {
								newY2 = 0 * 1.0;
								newX2 = (tempy2 - tempy1) / (tempx2 - tempx1) * (newX2 - tempx1) + tempy1;
								////cout << "DETECTED P1[1] = 1" << endl;
								////cout << "NewX1 = " << newX1 << endl;
								////cout << "NewY1 = " << newY1 << endl;
								////cout << "NewX2 = " << newX2 << endl;
								////cout << "NewY2 = " << newY2 << endl;

								newLine->x1 = newX1;
								newLine->y1 = newY1;
								newLine->x2 = newX2;
								newLine->y2 = newY2;

								point1Code = pointCode1Giver(newLine);
								point2Code = pointCode2Giver(newLine);

								resultOr = point1Code | point2Code;
								resultAnd = point1Code & point2Code;

								////cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
								////cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside


								//std:://cout << std::bitset<4>(point1Code) << "\n";
								//std:://cout << std::bitset<4>(point2Code) << "\n";

								if (resultAnd != 0) {
								///	//cout << "Line is not on plane" << endl;
									break;
								}
								if (resultOr == 0) {
								//	//cout << "Completely Inside" << endl;
									break;
								}

							}
						}

						if (i == 2) {
							if (p1[i] == '1') {
								newX1 = 500 * 1.0;
								newY1 = (tempy2 - tempy1) / (tempx2 - tempx1) * (newX1 - tempx1) + tempy1;
								////cout << "DETECTED P1[3] = 1" << endl;
								////cout << "NewX1 = " << newX1 << endl;
								////cout << "NewY1 = " << newY1 << endl;
								////cout << "NewX2 = " << newX2 << endl;
								////cout << "NewY2 = " << newY2 << endl;
								newLine->x1 = newX1;
								newLine->y1 = newY1;
								newLine->x2 = newX2;
								newLine->y2 = newY2;


								point1Code = pointCode1Giver(newLine);
								point2Code = pointCode2Giver(newLine);

								resultOr = point1Code | point2Code;
								resultAnd = point1Code & point2Code;

								////cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
								////cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside


								//std:://cout << std::bitset<4>(point1Code) << "\n";
								//std:://cout << std::bitset<4>(point2Code) << "\n";

								if (resultAnd != 0) {
								//	//cout << "Line is not on plane" << endl;
									break;
								}
								if (resultOr == 0) {
									////cout << "Completely Inside" << endl;
									break;
								}

							}

							if (p2[i] == '1') {
								newX2 = 1.0 * 500;

								//newY2 = (newLine->y1 - newLine->y2) / (newLine->x1 - newLine->x2) * (newX2 - newLine->x2) + newLine->y2;
								newY2 = (tempy1 - tempy2) / (tempx1 - tempx2) * (newX2 - tempx2) + tempy2;

								////cout << "DETECTED P2[3] = 1" << endl;
								////cout << "NewX1 = " << newX1 << endl;
								////cout << "NewY1 = " << newY1 << endl;
								////cout << "NewX2 = " << newX2 << endl;
								////cout << "NewY2 = " << newY2 << endl;

								newLine->x1 = newX1;
								newLine->y1 = newY1;
								newLine->x2 = newX2;
								newLine->y2 = newY2;

								point1Code = pointCode1Giver(newLine);
								point2Code = pointCode2Giver(newLine);

								resultOr = point1Code | point2Code;
								resultAnd = point1Code & point2Code;

								////cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
								//////cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside


								//std:://cout << std::bitset<4>(point1Code) << "\n";
								//std:://cout << std::bitset<4>(point2Code) << "\n";

								if (resultAnd != 0) {
									////cout << "Line is not on plane" << endl;
									break;
								}

								if (resultOr == 0) {
									////cout << "Completely Inside" << endl;
									break;
								}
							}
						}

						if (i == 3) {
							if (p1[i] == '1') {
								newX1 = 0 * 1.0;
								newY1 = (tempy2 - tempy1) / (tempx2 - tempx1) * (newX1 - tempx1) + tempy1;
								////cout << "DETECTED P1[4] = 1" << endl;
								////cout << "NewX1 = " << newX1 << endl;
								////cout << "NewY1 = " << newY1 << endl;
								////cout << "NewX2 = " << newX2 << endl;
								////cout << "NewY2 = " << newY2 << endl;
								newLine->x1 = newX1;
								newLine->y1 = newY1;
								newLine->x2 = newX2;
								newLine->y2 = newY2;


								point1Code = pointCode1Giver(newLine);
								point2Code = pointCode2Giver(newLine);

								resultOr = point1Code | point2Code;
								resultAnd = point1Code & point2Code;

								////cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
								////cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside


								//std:://cout << std::bitset<4>(point1Code) << "\n";
								//std:://cout << std::bitset<4>(point2Code) << "\n";

								if (resultAnd != 0) {
								//	//cout << "Line is not on plane" << endl;
									break;
								}
								if (resultOr == 0) {
								//	//cout << "Completely Inside" << endl;
									break;
								}


							}

							if (p2[i] == '1') {
								newX2 = 0 * 1.0;
								newY2 = (tempy2 - tempy1) / (tempx2 - tempx1) * (newX2 - tempx1) + tempy1;
								////cout << "DETECTED P2[4] = 1" << endl;
								////cout << "NewX1 = " << newX1 << endl;
								////cout << "NewY1 = " << newY1 << endl;
								////cout << "NewX2 = " << newX2 << endl;
								////cout << "NewY2 = " << newY2 << endl;

								newLine->x1 = newX1;
								newLine->y1 = newY1;
								newLine->x2 = newX2;
								newLine->y2 = newY2;


								point1Code = pointCode1Giver(newLine);
								point2Code = pointCode2Giver(newLine);

								resultOr = point1Code | point2Code;
								resultAnd = point1Code & point2Code;

								////cout << "ResultAnd = " << resultAnd << endl;  //if != 0, completely outside
								////cout << "ResultOr = " << resultOr << endl;  //if = 0, completely inside


								//std:://cout << std::bitset<4>(point1Code) << "\n";
								//std:://cout << std::bitset<4>(point2Code) << "\n";

								if (resultAnd != 0) {
								//	//cout << "Line is not on plane" << endl;
									break;
								}

								if (resultOr == 0) {
									////cout << "Completely Inside" << endl;
									break;
								}
							}

						}
					}

					newLine->x1 = newX1;
					newLine->y1 = newY1;
					newLine->x2 = newX2;
					newLine->y2 = newY2;

					////cout << "test" << newLine->x1 << "  " << newLine->y1 << "   " << newLine->x2 << "  " << newLine->y2 << "  " << endl;

					//if current point is inside completely
					if (resultAnd == 0) {
					//	//cout << "drawing";
						float x1 = newLine->x1;
						float y1 = newLine->y1;
						//float slope = yChange / xChange;
						////cout << "Slope = " << slope;

						int counter;

						if ((newLine->x2 - newLine->x1) >= (newLine->y2 - newLine->y1)) {
							counter = (newLine->x2 - newLine->x1);
						}

						if ((newLine->y2 - newLine->y1) >= (newLine->x2 - newLine->x1)) {
							counter = (newLine->y2 - newLine->y1);
						}


						float yChange = (newLine->y2 - newLine->y1);
						yChange = yChange / counter;
						float xChange = (newLine->x2 - newLine->x1);
						xChange = xChange / counter;


						////cout << "test" << newLine->x1 << "  " << newLine->y1 << "   " << newLine->x2 << "  " << newLine->y2 << "  " << endl;
						int i = 1;
						while (i < counter) {
							xpm[500 - y1 + 8][x1 + 1] = 'X';
							x1 = x1 + xChange;
							y1 = y1 + yChange;
							i++;
						}

					}
				}

			}
		}
	}

	//draws to xpm file
	for (int i = 0; i < xpm.size(); i++) {
		myfile << xpm[i];
	}
	for (int i = 0; i < xpm.size(); i++) {
		cout << xpm[i];
	}
	

	

}

//for getting updated points, used integers so it was easier to read
int pointCode1Giver(Line* line) {

	int point1Code;

	if (line->x1 > 500 && line->y1 > 500) {
		//point1Code = "1010";
		point1Code = 10;
	}
	if (line->x1 < 0 && line->y1 > 500) {
		//point1Code = "1001";
		point1Code = 9;
	}
	if (line->x1 >= 0 && line->x1 <= 500 && line->y1 > 500) {
		//point1Code = "1000";
		point1Code = 8;
	}
	if (line->x1 < 0 && line->y1 <= 500 && line->y1 >= 0) {
		//point1Code = "0001";
		point1Code = 1;
	}
	if (line->x1 < 0 && line->y1 < 0) {
		//point1Code = "0101";
		point1Code = 5;
	}
	if (line->x1 >= 0 && line->x1 <= 500 && line->y1 < 0) {
		//point1Code = "0100";
		point1Code = 4;
	}
	if (line->x1 > 500 && line->y1 < 0) {
		//point1Code = "0110";
		point1Code = 6;
	}
	if (line->x1 > 500 && line->y1 >= 0 && line->y1 <= 500) {
		//point1Code = "0010";
		point1Code = 2;
	}
	if (line->x1 <= 500 && line->x1 >= 0 && line->y1 >= 0 && line->y1 <= 500) {
		//point1Code = "0000";
		point1Code = 0;
	}

	return point1Code;
}

vector<string> printXPM(Polygon* polygon, vector<string> xpm) {
	//cout << "Polygon Lines" << " " << endl;
	//for (int i = 0; i < polygon->polyLines.size(); i++) {
		////cout << polygon->polyLines[i]->x1 << " " << polygon->polyLines[i]->y1 << " " << polygon->polyLines[i]->x2 << " " << polygon->polyLines[i]->y2 << " " << endl;
	//}
	for (int i = 0; i < polygon->polyLines.size(); i++) {
		

		


	
		Line* tempLine = polygon->polyLines[i];
		bool temp = isFullyInside(tempLine);
		//cout << "Current Line  " << tempLine->x1 << "  " << tempLine->y1 << "  " << tempLine->x2 << "  " << tempLine->y2 << endl;
		

		if (tempLine->x1 != tempLine->x2 && tempLine->y1 != tempLine->y2) {

			float x1 = tempLine->x1;
			float y1 = tempLine->y1;
			int counter;

			if ((tempLine->y2 - tempLine->y1) >= (tempLine->x2 - tempLine->x1)) {
				counter = (tempLine->y2 - tempLine->y1);

			}

			else if ((tempLine->y2 - tempLine->y1) <= (tempLine->x2 - tempLine->x1)) {

				counter = (tempLine->x2 - tempLine->x1);
			}

			//cout << counter;
			
			if (counter < 0) {
				int tempx1 = tempLine->x1;
				int tempx2 = tempLine->x2;
				int tempy1 = tempLine->y1;
				int tempy2 = tempLine->y2;

				tempLine->x1 = tempx2;
				tempLine->x2 = tempx1;
				tempLine->y1 = tempy2;
				tempLine->y2 = tempy1;

				if ((tempLine->y2 - tempLine->y1) >= (tempLine->x2 - tempLine->x1)) {
					counter = (tempLine->y2 - tempLine->y1);

				}

				else if ((tempLine->y2 - tempLine->y1) <= (tempLine->x2 - tempLine->x1)) {
					counter = (tempLine->x2 - tempLine->x1);
				}

				x1 = tempLine->x1;
				y1 = tempLine->y1;


			}



			
			float yChange = (tempLine->y2 - tempLine->y1);
			float xChange = (tempLine->x2 - tempLine->x1);

			xChange = xChange / counter;
			yChange = yChange / counter;


			int k = 1;
			while (k < counter) {
				//cout << "k = " << k << endl;
				////cout << "hello" << endl;
				if ((x1)!=0) {
					
					//cout << "x1 = " << x1 << endl;
					xpm[507 - y1][x1] = 'X';
					x1 = x1 + xChange;
					y1 = y1 + yChange;
					
				}
				k++;
			}
		}

		else {
			

			if (tempLine->y1 == tempLine->y2) {

				if (tempLine->x1 < tempLine->x2) {
					for (int i = tempLine->x1 + 1; i < tempLine->x2 + 1; i++) {
						if ((i - 1) >= 0 && (i - 1) <= 500) {
							////cout << i - 1 << endl;
							xpm[507 - tempLine->y1][i] = 'X';
						}
						
					}
				}

				else {

					for (int i = tempLine->x2 + 1; i < tempLine->x1 + 1; i++) {
						if ((i - 1) >= 0 && (i - 1) <= 500) {
							xpm[507 - tempLine->y1][i] = 'X';
						}
					}
				}
			}

			if (tempLine->x1 == tempLine->x2) {
				
				if (tempLine->y1 < tempLine->y2) {
					for (int i = 507 - tempLine->y2; i < 507 - tempLine->y1; i++) {
						if ((tempLine->x1) >= 0 && (tempLine->x1) <= 500) {
							xpm[i][tempLine->x1] = 'X';
						}
					}
				}
				else {
					////cout << "got here";
					for (int i = 507 - tempLine->y1; i < 507 - tempLine->y2; i++) {
						if ((tempLine->x1) >= 0 && (tempLine->x1) <= 500) {
							xpm[i][tempLine->x1] = 'X';
						}
					}
				}
			}
		}
	}

	
	for (int i = 7; i < xpm.size(); i++) {
		xpm[i][0] = '"';
	}
	return xpm;
}
bool isFullyInside(Line * line)
{
	int x1 = line->x1;
	int x2 = line->x2;
	int y1 = line->y1;
	int y2 = line->y2;

	////cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << endl;
	if (x1 > 0 && x1 < -500) {
		if (y1 > 0 && y1 < 500) {
			return true;
		}
	}
		if (x2 > 0 && x2 < 500) {
			if (y2 > 0 && y2 < 500) {

				////cout << "This line is fully inside : " << x1 << "  " << y1 << "  " << x2 << "  " << y2 << "  " << endl;
				////cout << "Fully Inside Clipping Window";
				return true;
			}
		
			
		}
	

	return false;
}

bool isPointInside(int x, int y) {
	if (x > 0 && x < 500 && y > 0 && y < 500) {
		return true;
		////cout << "point " << x << " " << y << "is inside" << endl;
	}

	else {
		return false;
	}
}

Vertice* intersectionOfPoints(Vertice* p1, Vertice* p2, Vertice* p3, Vertice* p4)
{
	Vertice* intersectionPoint = new Vertice(1, 2);


	float l1p1x = p1->xCoord * 1.0;
	float l1p2x = p2->xCoord * 1.0;
	float l1p1y = p1->yCoord * 1.0;
	float l1p2y = p2->yCoord * 1.0;

	float l2p1x = p3->xCoord * 1.0;
	float l2p2x = p4->xCoord * 1.0;
	float l2p1y = p3->yCoord * 1.0;
	float l2p2y = p4->yCoord * 1.0;

	float slope1;
	float slope2;

	if (l1p1y == l1p2y) {
		slope1 = 0;
	}

	else {
		slope1 = (l1p2y - l1p1y) / (l1p2x - l1p1x);

	}

	if (l2p1y == l2p2y) {
		slope2 = 0;
	}

	else {
		slope2 = (l2p2y - l2p1y) / (l2p2x - l2p1x);
	}




		////cout << "Slope 1 = " << slope1 << endl;
		////cout << "Slope 2 = " << slope2 << endl;

		float line1b = slope1*(l1p1x)-l1p1y;
		line1b = -line1b;

		float line2b = slope2*(l2p1x)-l2p1y;
		line2b = -line2b;

		////cout << "Line Equation 2 : Y =  " << slope2 << "x" << "+" << line2b << endl;
		////cout << "Line Equation 1 : Y =  " << slope1 << "x" << "+" << line1b << endl;

		intersectionPoint->xCoord = (line2b - line1b) / (slope1 - slope2);
		intersectionPoint->yCoord = ((slope1*line2b) - (slope2*line1b)) / (slope1 - slope2);

		if (l2p1x == l2p2x) {
			intersectionPoint->xCoord = l2p1x;
			intersectionPoint->yCoord = l1p1y;
		}

		if (l1p1x == l1p2x) {
			intersectionPoint->xCoord = l1p1x;
			intersectionPoint->yCoord = l2p1y;
		}



		////cout << "Intersection Point = " << intersectionPoint->xCoord << " , " << intersectionPoint->yCoord << endl;
		return intersectionPoint;
	
}

int pointCode2Giver(Line* line) {

	int point2Code;

	if (line->x2 > 500 && line->y2 > 500) {
		//point2Code = "1010";
		point2Code = 10;
	}
	if (line->x2 < 0 && line->y2 > 500) {
		//point2Code = "1001";
		point2Code = 9;
	}
	if (line->x2 >= 0 && line->x2 <= 500 && line->y2 > 500) {
		//point2Code = "1000";
		point2Code = 8;
	}
	if (line->x2 < 0 && line->y2 <= 500 && line->y2 >= 0) {
		//point2Code = "0001";
		point2Code = 1;
	}
	if (line->x2 < 0 && line->y2 < 0) {
		//point2Code = "0101";
		point2Code = 5;
	}
	if (line->x2 >= 0 && line->x2 <= 500 && line->y2 < 0) {
		//point2Code = "0100";
		point2Code = 4;
	}
	if (line->x2 > 500 && line->y2 < 0) {
		//point2Code = "0110";
		point2Code = 6;
	}
	if (line->x2 > 500 && line->y2 >= 0 && line->y2 <= 500) {
		//point2Code = "0010";
		point2Code = 2;
	}
	if (line->x2 <= 500 && line->x2 >= 0 && line->y2 >= 0 && line->y2 <= 500) {
		//point2Code = "0000";
		point2Code = 0;
	}

	return point2Code;

}

vector<string> fillPolygon(Polygon* polygon, vector<string> xpm) {
	vector <Line*> scanLines;
	vector <Line*> fillLines;
	

	for (int i = 0; i < 501; i++) {
		Line* newLine = new Line(0, i, 500, i);
		scanLines.push_back(newLine);
	}

	for (int j = 0; j < 500; j++) {
		vector <Vertice*> intersectionPointList;

		for (int k = 0; k < polygon->polyLines.size(); k++) {

			////cout << "j = " << j << endl;
			Vertice* scanLine1 = new Vertice(scanLines[j]->x1, scanLines[j]->y1);
			Vertice* scanLine2 = new Vertice(scanLines[j]->x2, scanLines[j]->y2);

			Vertice* polyLines1 = new Vertice(polygon->polyLines[k]->x1, polygon->polyLines[k]->y1);
			Vertice* polyLines2 = new Vertice(polygon->polyLines[k]->x2, polygon->polyLines[k]->y2);

			Vertice* intersectionPoint = intersectionOfPoints(scanLine1, scanLine2, polyLines1, polyLines2);
			intersectionPoint->yCoord = scanLine1->yCoord;
		

			if (intersectionPoint->xCoord >= 0 && intersectionPoint->yCoord >= 0) {
				////cout << "###########################################################" << endl;
				if ((scanLine1->yCoord >= polyLines1->yCoord && scanLine1->yCoord <= polyLines2->yCoord) || (scanLine1->yCoord <= polyLines1->yCoord && scanLine1->yCoord >= polyLines2->yCoord)) {
					////cout << "Valid Intersection found" << endl;
					////cout << "ScanLine are " << scanLine1->xCoord << " " << scanLine1->yCoord << "  " << scanLine2->xCoord << " " << scanLine2->yCoord << endl;
					////cout << "PolyLines are " << polyLines1->xCoord << " " << polyLines1->yCoord << "  " << polyLines2->xCoord << " " << polyLines2->yCoord << endl;
					////cout << "Intersection point is " << intersectionPoint->xCoord << " " << intersectionPoint->yCoord << endl;
					intersectionPointList.push_back(intersectionPoint);
				}
			}

			else {
				if (polyLines1->yCoord != 275) {
					////cout << "###########Non Valid Intersection Found!######" << endl;
					////cout << "Intersection between scan line " << scanLine1->xCoord << "  " << scanLine1->yCoord << "  " << scanLine2->xCoord << "  " << scanLine2->yCoord;
					////cout << " And polyLine " << polyLines1->xCoord << "  " << polyLines1->yCoord << "  " << polyLines2->xCoord << "  " << polyLines2->yCoord << " = ";
					////cout << intersectionPoint->xCoord << " " << intersectionPoint->yCoord << endl;
					////cout << "##############################################" << endl << endl;
				}


			}




		}
			sort(intersectionPointList.begin(), intersectionPointList.end(), sortVector);
			int counter = 0;
			////cout << "Current intersection point list" << endl;
		

			if (intersectionPointList.size() == 4) {
				intersectionPointList[0]->yCoord = intersectionPointList[2]->yCoord;
				intersectionPointList[3]->yCoord = intersectionPointList[2]->yCoord;
			}
			

			//else if(intersectionPointList)

			for (int i = 0; i < intersectionPointList.size(); i++) {
				////cout << intersectionPointList[i]->xCoord << "  " << intersectionPointList[i]->yCoord << endl;
			}
			
			if (intersectionPointList.size() % 2 == 0) {
				for (int i = 0; i < intersectionPointList.size(); i += 2) {

					Line* newLine = new Line(intersectionPointList[i]->xCoord, intersectionPointList[i]->yCoord, intersectionPointList[i + 1]->xCoord, intersectionPointList[i + 1]->yCoord);
					if (newLine->x1 < newLine->x2) {
						////cout << "#########" << endl;
						for (int i = newLine->x1 + 1; i < newLine->x2 + 2; i++) {
							if (i == 0) {
								i = 1;
							}
							if (xpm[500 - newLine->y1].size() == 504) {
								xpm[507 - newLine->y1][i - 1] = 'X';

							}
						}
					}

					else {
						////cout << "#########" << endl;
						for (int i = newLine->x2 + 1; i < newLine->x1 + 2; i++) {

							if (i == 0) {
								i = 1;
							}
							if (xpm[500 - newLine->y1].size() == 504) {
								xpm[507 - newLine->y1][i - 1] = 'X';

							}
						}
					}



				}
			}
	}
	for (int i = 7; i < xpm.size(); i++) {
		xpm[i][0] = '"';
	}
	return xpm;
	return xpm;

}

bool sortVector(Vertice* vertice1, Vertice* vertice2)
{
	return vertice1->xCoord < vertice2->xCoord;
}



Polygon* createPolygon(vector<string> polyList) {
	vector<string> newList = polyList;
	vector <Line*> storage2;

	int i = 0;
	while (i < newList.size() - 4) {
		Line* newLine = new Line(atoi(newList[i].c_str()), atoi(newList[i + 1].c_str()), atoi(newList[i + 3].c_str()), atoi(newList[i + 4].c_str()));
		storage2.push_back(newLine);
		i += 3;

	}


	int x1 = storage2[storage2.size() - 1]->x2;
	int y1 = storage2[storage2.size() - 1]->y2;

	int x2 = storage2[0]->x1;
	int y2 = storage2[0]->y1;
	Line* newLine2 = new Line(x1, y1, x2, y2);

	storage2.insert(storage2.begin(), newLine2);


	Polygon* newPolygon2 = new Polygon(storage2);
	
	return newPolygon2;
}

Polygon* scalePolygon(Polygon* polygonVector, float scaleFactor) {
	Polygon* newPolygonList;
	vector<int> verticesList;
	vector<Line*> lineList;

	float scaleResult[3][1];
	float scaleResult2[3][1];
	float scaleMatrix[3][3];
	float initialMatrix[3][1];
	float initialMatrix2[3][1];

	scaleMatrix[0][0] = scaleFactor;
	scaleMatrix[0][1] = 0;
	scaleMatrix[0][2] = 0;
	scaleMatrix[1][0] = 0;
	scaleMatrix[1][1] = scaleFactor;
	scaleMatrix[1][2] = 0;
	scaleMatrix[2][0] = 0;
	scaleMatrix[2][1] = 0;
	scaleMatrix[2][2] = 1;

	scaleResult[0][0] = 0;
	scaleResult[0][1] = 0;
	scaleResult[0][2] = 0;
		
	for (int k = 0; k < polygonVector->polyLines.size(); k++) {

		////cout << "We are currently on vertice = " << k << endl;

			initialMatrix[0][0] = polygonVector->polyLines[k]->x1 * 1.0;
			initialMatrix[0][1] = polygonVector->polyLines[k]->y1 * 1.0;
			initialMatrix[0][2] = 1;

			////cout << initialMatrix[0][0] << endl;
			////cout << initialMatrix[0][1] << endl;
			////cout << initialMatrix[0][2] << endl;

			////cout << "x1 y1 = " << polygonVector->polyLines[k]->x1 << polygonVector->polyLines[k]->y1 << endl;

		
			scaleResult[0][0] = (scaleMatrix[0][0] * initialMatrix[0][0]) + (scaleMatrix[0][1] * initialMatrix[0][0]) + (scaleMatrix[0][2] * initialMatrix[0][0]);
			scaleResult[0][1] = (scaleMatrix[1][0] * initialMatrix[0][1]) + (scaleMatrix[1][1] * initialMatrix[0][1]) + (scaleMatrix[1][2] * initialMatrix[0][1]);
			scaleResult[0][2] = (scaleMatrix[2][0] * initialMatrix[0][2]) + (scaleMatrix[2][1] * initialMatrix[0][2]) + (scaleMatrix[2][2] * initialMatrix[0][2]);

			polygonVector->polyLines[k]->x1 = scaleResult[0][0];
			polygonVector->polyLines[k]->y1 = scaleResult[0][1];		

		}

	for (int k = 0; k < polygonVector->polyLines.size(); k++) {


		////cout << "We are currently on vertice = " << k << endl;

		initialMatrix[0][0] = polygonVector->polyLines[k]->x2 * 1.0;
		initialMatrix[0][1] = polygonVector->polyLines[k]->y2 * 1.0;
		initialMatrix[0][2] = 1;

		////cout << initialMatrix[0][0] << endl;
		////cout << initialMatrix[0][1] << endl;
		////cout << initialMatrix[0][2] << endl;

		////cout << "x1 y1 = " << polygonVector->polyLines[k]->x2 << polygonVector->polyLines[k]->y2 << endl;

		scaleResult[0][0] = (scaleMatrix[0][0] * initialMatrix[0][0]) + (scaleMatrix[0][1] * initialMatrix[0][0]) + (scaleMatrix[0][2] * initialMatrix[0][0]);
		scaleResult[0][1] = (scaleMatrix[1][0] * initialMatrix[0][1]) + (scaleMatrix[1][1] * initialMatrix[0][1]) + (scaleMatrix[1][2] * initialMatrix[0][1]);
		scaleResult[0][2] = (scaleMatrix[2][0] * initialMatrix[0][2]) + (scaleMatrix[2][1] * initialMatrix[0][2]) + (scaleMatrix[2][2] * initialMatrix[0][2]);

		polygonVector->polyLines[k]->x2 = scaleResult[0][0];
		polygonVector->polyLines[k]->y2 = scaleResult[0][1];

	}

	return polygonVector;
	
}

Polygon* rotatePolygon(Polygon* polygonVector, float rotationFactor) {
	float pi = 3.14;
	Polygon* newPolygonList;
	vector<int> verticesList;
	vector<Line*> lineList;

	float rotationResult[3][1];
	float rotationResult2[3][1];
	float rotationMatrix[3][3];
	float initialMatrix[3][1];
	float initialMatrix2[3][1];

	rotationMatrix[0][0] = cos((rotationFactor * pi)/180);
	rotationMatrix[0][1] = sin((rotationFactor * pi) / 180);
	rotationMatrix[0][2] = 0;

	rotationMatrix[1][0] = -sin((rotationFactor * pi) / 180);
	rotationMatrix[1][1] = cos((rotationFactor * pi) / 180);
	rotationMatrix[1][2] = 0;

	rotationMatrix[2][0] = 0;
	rotationMatrix[2][1] = 0;
	rotationMatrix[2][2] = 1;

	rotationResult[0][0] = 0;
	rotationResult[0][1] = 0;
	rotationResult[0][2] = 0;

	for (int k = 0; k < polygonVector->polyLines.size(); k++) {

		////cout << "We are currently on vertice = " << k << endl;

		initialMatrix[0][0] = polygonVector->polyLines[k]->x1 * 1.0;
		initialMatrix[0][1] = polygonVector->polyLines[k]->y1 * 1.0;
		initialMatrix[0][2] = 1;

		////cout << initialMatrix[0][0] << endl;
		////cout << initialMatrix[0][1] << endl;
		////cout << initialMatrix[0][2] << endl;

		////cout << "x1 y1 = " << polygonVector->polyLines[k]->x1 << polygonVector->polyLines[k]->y1 << endl;

		int i = 0;
		while (i < 3) {
			int j = 0;
			while (j < 1) {
				rotationResult[i][j] = 0;
				int k = 0;
				while (k < 3) {
					rotationResult[i][j] = rotationResult[i][j] + initialMatrix[i][k] * rotationMatrix[k][j];
					k++;
				}
				j++;
			}
			i++;
		}


		polygonVector->polyLines[k]->x1 = rotationResult[0][0];
		polygonVector->polyLines[k]->y1 = rotationResult[0][1];

	}

	for (int k = 0; k < polygonVector->polyLines.size(); k++) {



		////cout << "We are currently on vertice = " << k << endl;

		initialMatrix[0][0] = polygonVector->polyLines[k]->x2 * 1.0;
		initialMatrix[0][1] = polygonVector->polyLines[k]->y2 * 1.0;
		initialMatrix[0][2] = 1;

		////cout << initialMatrix[0][0] << endl;
		////cout << initialMatrix[0][1] << endl;
		////cout << initialMatrix[0][2] << endl;

		////cout << "x1 y1 = " << polygonVector->polyLines[k]->x2 << polygonVector->polyLines[k]->y2 << endl;


		int i = 0;
		while (i < 3) {
			int j = 0;
			while(j < 1){
				rotationResult[i][j] = 0;
				int k = 0;
				while(k < 3) {
					rotationResult[i][j] = rotationResult[i][j] + initialMatrix[i][k] * rotationMatrix[k][j];
					k++;
				}
				j++;
			}
			i++;
		}
	

		polygonVector->polyLines[k]->x2 = rotationResult[0][0];
		polygonVector->polyLines[k]->y2 = rotationResult[0][1];

	}

	return polygonVector;

}

Polygon * xTranslatePolygon(Polygon * polygonVector, float xTransFactor)
{

	////cout << xTransFactor << endl;
	Polygon* newPolygonList;
	vector<int> verticesList;
	vector<Line*> lineList;

	float xTransResult[3][1];
	float xTransResult2[3][1];
	float xTransMatrix[3][3];
	float initialMatrix[3][1];
	float initialMatrix2[3][1];

	xTransMatrix[0][0] = 1;
	xTransMatrix[0][1] = 0;
	xTransMatrix[0][2] = 0;

	xTransMatrix[1][0] = 0;
	xTransMatrix[1][1] = 1;
	xTransMatrix[1][2] = 0;

	xTransMatrix[2][0] = xTransFactor;
	xTransMatrix[2][1] = 0;
	xTransMatrix[2][2] = 1;

	xTransResult[0][0] = 0;
	xTransResult[0][1] = 0;
	xTransResult[0][2] = 0;

	for (int k = 0; k < polygonVector->polyLines.size(); k++) {
		
		////cout << "We are currently on vertice = " << k << endl;

		initialMatrix[0][0] = polygonVector->polyLines[k]->x1 * 1.0;
		initialMatrix[0][1] = polygonVector->polyLines[k]->y1 * 1.0;
		initialMatrix[0][2] = 1;

		////cout << initialMatrix[0][0] << endl;
		////cout << initialMatrix[0][1] << endl;
		////cout << initialMatrix[0][2] << endl;

		////cout << "x1 y1 = " << polygonVector->polyLines[k]->x1 << " " <<  polygonVector->polyLines[k]->y1 << endl;

		int i = 0;
		while (i < 3) {
			int j = 0;
			while (j < 1) {
				xTransResult[i][j] = 0;
				int k = 0;
				while (k < 3) {
					xTransResult[i][j] = xTransResult[i][j] + initialMatrix[i][k] * xTransMatrix[k][j];
					k++;
				}
				j++;
			}
			i++;
		}
		
		polygonVector->polyLines[k]->x1 = xTransResult[0][0];
	

		////cout << "New Points = " << polygonVector->polyLines[k]->x1 << " " << polygonVector->polyLines[k]->y1 << endl;

	}

	for (int k = 0; k < polygonVector->polyLines.size(); k++) {



		////cout << "We are currently on vertice = " << k << endl;

		initialMatrix[0][0] = polygonVector->polyLines[k]->x2 * 1.0;
		initialMatrix[0][1] = polygonVector->polyLines[k]->y2 * 1.0;
		initialMatrix[0][2] = 1;

		////cout << initialMatrix[0][0] << endl;
		/////cout << initialMatrix[0][1] << endl;
		////cout << initialMatrix[0][2] << endl;

		////cout << "x1 y1 = " << polygonVector->polyLines[k]->x2 << " " <<  polygonVector->polyLines[k]->y2 << endl;


		int i = 0;
		while (i < 3) {
			int j = 0;
			while (j < 1) {
				xTransResult[i][j] = 0;
				int k = 0;
				while (k < 3) {
					xTransResult[i][j] = xTransResult[i][j] + initialMatrix[i][k] * xTransMatrix[k][j];
					k++;
				}
				j++;
			}
			i++;
		}

		polygonVector->polyLines[k]->x2 = xTransResult[0][0];
		////cout << "New Points = " << polygonVector->polyLines[k]->x2 << " " << polygonVector->polyLines[k]->y2 << endl;

	}

	return polygonVector;
}

Polygon * yTranslatePolygon(Polygon * polygonVector, float yTransFactor)
{

	Polygon* newPolygonList;
	vector<int> verticesList;
	vector<Line*> lineList;

	float yTransResult[3][1];
	float yTransResult2[3][1];
	float yTransMatrix[3][3];
	float initialMatrix[3][1];
	float initialMatrix2[3][1];

	yTransMatrix[0][0] = 1;
	yTransMatrix[0][1] = 0;
	yTransMatrix[0][2] = 0;

	yTransMatrix[1][0] = 0;
	yTransMatrix[1][1] = 1;
	yTransMatrix[1][2] = 0;

	yTransMatrix[2][0] = 0;
	yTransMatrix[2][1] = yTransFactor;
	yTransMatrix[2][2] = 1;

	yTransResult[0][0] = 0;
	yTransResult[0][1] = 0;
	yTransResult[0][2] = 0;

	for (int k = 0; k < polygonVector->polyLines.size(); k++) {

		////cout << "We are currently on vertice = " << k << endl;

		initialMatrix[0][0] = polygonVector->polyLines[k]->x1 * 1.0;
		initialMatrix[0][1] = polygonVector->polyLines[k]->y1 * 1.0;
		initialMatrix[0][2] = 1;

		////cout << initialMatrix[0][0] << endl;
		////cout << initialMatrix[0][1] << endl;
		////cout << initialMatrix[0][2] << endl;

		////cout << "x1 y1 = " << polygonVector->polyLines[k]->x1 << " " <<  polygonVector->polyLines[k]->y1 << endl;

		int i = 0;
		while (i < 3) {
			int j = 0;
			while (j < 1) {
				yTransResult[i][j] = 0;
				int k = 0;
				while (k < 3) {
					yTransResult[i][j] = yTransResult[i][j] + initialMatrix[i][k] * yTransMatrix[k][j];
					k++;
				}
				j++;
			}
			i++;
		}

		polygonVector->polyLines[k]->y1 = yTransResult[0][1] + yTransFactor;


		////cout << "New Points = " << polygonVector->polyLines[k]->x1 << " " << polygonVector->polyLines[k]->y1 << endl;

	}

	for (int k = 0; k < polygonVector->polyLines.size(); k++) {



		////cout << "We are currently on vertice = " << k << endl;

		initialMatrix[0][0] = polygonVector->polyLines[k]->x2 * 1.0;
		initialMatrix[0][1] = polygonVector->polyLines[k]->y2 * 1.0;
		initialMatrix[0][2] = 1;

		////cout << initialMatrix[0][0] << endl;
		/////cout << initialMatrix[0][1] << endl;
		////cout << initialMatrix[0][2] << endl;

		////cout << "x1 y1 = " << polygonVector->polyLines[k]->x2 << " " <<  polygonVector->polyLines[k]->y2 << endl;


		int i = 0;
		while (i < 3) {
			int j = 0;
			while (j < 1) {
				yTransResult[i][j] = 0;
				int k = 0;
				while (k < 3) {
					yTransResult[i][j] = yTransResult[i][j] + initialMatrix[i][k] * yTransMatrix[k][j];
					k++;
				}
				j++;
			}
			i++;
		}

		polygonVector->polyLines[k]->y2 = yTransResult[0][1]+yTransFactor;
		////cout << "New Points = " << polygonVector->polyLines[k]->x2 << " " << polygonVector->polyLines[k]->y2 << endl;

	}

	return polygonVector;
}

Polygon * wwToScreen(Polygon * polygonVector, int upperx, int uppery, int lowerx, int lowery)
{
	return polygonVector;
}

