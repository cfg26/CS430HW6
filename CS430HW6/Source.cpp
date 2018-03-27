#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <istream>
#include <iterator>
#include <bitset>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "Vertice.h"
#include "Face.h"
#include "Polygon.h"

using namespace std;

int viewportLowerX = 0;
int viewportUpperX = 499;
int viewportLowerY = 0;
int viewPortUpperY = 499;

float PRPX = 0.0;
float PRPY = 0.0;
float PRPZ = 1.0;

float VRPX = 0.0;
float VRPY = 0.0;
float VRPZ = 0.0;

float VPNX = 0.0;
float VPNY = 0.0;
float VPNZ = -1.0;

float VUPX = 0.0;
float VUPY = 1.0;
float VUPZ = 0.0;

float VRCLowerU = -0.7;
float VRCLowerV = -0.7;
float VRCUpperU = 0.7;
float VRCUpperV = 0.7;

float front = 0.6;
float back = -0.6;

bool parallelProjection = false;
float projectionMatrix[4][4];
float viewMatrix[4][4];
float finalMatrix[4][4];
float zbuffer2[500][500];

vector <string> xpm;
vector <string> zbuffer;

vector <string> polyLines;
vector <Vertice*> verticeList;
vector <Face*> faceList;
vector <Face*> faceList2;
vector <Face*> faceList3;
vector <Polygon*> polygonList;
vector <Polygon*> polygonList2;
vector <Polygon*> polygonList3;
vector <Polygon*> oldPolygons;
vector <Polygon*> newPolygons;
vector <Polygon*> newPolygons2;
vector <Polygon*> newPolygons3;
vector <Polygon*> testPolygons;

vector<string> setUpXPM(vector<string> inputXPM);
vector<string> setUpZBuffer(vector<string> inputZBuffer);
void writeXPM(vector<string> inputXPM);
void writeZBuffer(vector<string> inputXPM);
vector <Face*> createFaceList(string inFile);
vector <Polygon*> createPolygonList(vector<Face*> faceList);
void calculateViewMatrix();
void calculatePerspectiveProjectionMatrix();
void calculateParallelProjectionMatrix();
void calculateFinalMatrix();
//void updatePolygons();
vector <Polygon*> updatePolygons(vector <Polygon*> polygonList);
vector <Polygon*> clipping(vector <Polygon*> polygonList);

vector <Polygon*>  projectTo2d(vector <Polygon*> newPolygons);
vector<Polygon*> convertToViewPort(vector<Polygon*> newPolygons);
vector<string> printXPM(Polygon* polygon);
vector<string> fillPolygon(Polygon* polygon, vector<string> xpm);
bool sortVector(Vertice* vertice1, Vertice* vertice2);
Vertice* intersectionOfPoints(Vertice* p1, Vertice* p2, Vertice* p3, Vertice* p4);
void zbufferxpm(vector<Polygon*> newPolygons);
void zbufferxpm2(vector<Polygon*> newPolygons);
void zbufferxpm3(vector<Polygon*> newPolygons);



int main(int argc, char* argv[]) {
	string inFile;
	string fileName;
	string inFile2;
	string fileName2;
	string inFile3;
	string fileName3;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-f") == 0) {
			inFile = argv[i + 1];
			fileName = argv[i + 1];
		}
		if (strcmp(argv[i], "-g") == 0) {
			inFile2 = argv[i + 1];
			fileName2 = argv[i + 1];
		}
		if (strcmp(argv[i], "-i") == 0) {
			inFile3 = argv[i + 1];
			fileName3 = argv[i + 1];
		}
		if (strcmp(argv[i], "-j") == 0) {
			viewportLowerX = atof(argv[i + 1]);

		}
		if (strcmp(argv[i], "-k") == 0) {
			viewportLowerY = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-o") == 0) {
			viewportUpperX = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-p") == 0) {
			viewPortUpperY = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-x") == 0) {
			PRPX = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-y") == 0) {
			PRPY = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-z") == 0) {
			PRPZ = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-X") == 0) {
			VRPX = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-Y") == 0) {
			VRPY = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-Z") == 0) {
			VRPZ = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-q") == 0) {
			VPNX = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-r") == 0) {
			VPNY = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-w") == 0) {
			VPNZ = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-Q") == 0) {
			VUPX = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-R") == 0) {
			VUPY = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-W") == 0) {
			VUPZ = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-u") == 0) {
			VRCLowerU = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-v") == 0) {
			VRCLowerV = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-U") == 0) {
			VRCUpperU = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-V") == 0) {
			VRCUpperV = atof(argv[i + 1]);
		}
		if (strcmp(argv[i], "-P") == 0) {
			parallelProjection = true;
		}
		if (strcmp(argv[i], "-F") == 0) {
			front = atof(argv[i + 1]);

		}
		if (strcmp(argv[i], "-B") == 0) {
			back = atof(argv[i + 1]);
		}

	}



	for (int i = 0; i < 500; i++) {
		for (int k = 0; k < 500; k++) {
			zbuffer2[i][k] = -1;
		}

	}
	for (int i = 0; i < 500; i++) {
		for (int k = 0; k < 500; k++) {
			zbuffer2[i][k] = -1;
		}

	}
	

	vector <Polygon*> tempPolygon;

	if (inFile.size() != 0) {
		faceList = createFaceList(inFile);
		polygonList = createPolygonList(faceList);
		vector <Polygon*> tempPolygon(polygonList);
	}
	if (inFile2.size() != 0) {
		faceList2 = createFaceList(inFile2);
		polygonList2 = createPolygonList(faceList2);
		vector <Polygon*> tempPolygon2(polygonList2);

	}
	if (inFile3.size() != 0) {
		faceList3 = createFaceList(inFile3);
		polygonList3 = createPolygonList(faceList3);
		vector <Polygon*> tempPolygon3(polygonList3);
	}
	

	xpm = setUpXPM(xpm);
	writeXPM(xpm);
	zbuffer = setUpZBuffer(zbuffer);
	writeZBuffer(zbuffer);

	calculateViewMatrix();

	if (parallelProjection == true) {
		calculateParallelProjectionMatrix();
	}

	else {
		calculatePerspectiveProjectionMatrix();
	}

	calculateFinalMatrix();
	
	if (inFile.size() != 0) {
		polygonList = updatePolygons(polygonList);
	}
	if (inFile2.size() != 0) {
		polygonList2 = updatePolygons(polygonList2);

	}
	if (inFile3.size() != 0) {
		polygonList3 = updatePolygons(polygonList3);
	}

	if (inFile.size() != 0) {
		clipping(polygonList);
	}
	if (inFile2.size() != 0) {
		clipping(polygonList2);

	}
	if (inFile3.size() != 0) {
		clipping(polygonList3);
	}
	
	if (inFile.size() != 0) {
		polygonList = projectTo2d(polygonList);
	}
	if (inFile2.size() != 0) {
		polygonList2 = projectTo2d(polygonList2);

	}
	if (inFile3.size() != 0) {
		polygonList3 = projectTo2d(polygonList3);
	}
	

	if (inFile.size() != 0) {
		polygonList = convertToViewPort(polygonList);
	}
	if (inFile2.size() != 0) {
		polygonList2 = convertToViewPort(polygonList2);

	}
	if (inFile3.size() != 0) {
		polygonList3 = convertToViewPort(polygonList3);
	}
	/////////////////////////////////
	//cout << "hello";
	
	if (inFile.size() != 0) {
		if (polygonList.size() > 4000) {
			//cout << "< 4000" << endl;
			for (int i = 0; i < 3000; i++) {
				xpm = fillPolygon(polygonList[i], xpm);

			}
		}
		else {
			for (int i = 0; i < polygonList.size(); i++) {
				xpm = fillPolygon(polygonList[i], xpm);

			}
		}
	}
	
	if (inFile2.size() != 0) {
		if (polygonList2.size() > 4000) {
			//cout << "< 4000" << endl;
			for (int i = 0; i < 3000; i++) {
				
				xpm = fillPolygon(polygonList2[i], xpm);

			}
		}
		else {
			for (int i = 0; i < polygonList2.size(); i++) {
				xpm = fillPolygon(polygonList2[i], xpm);

			}
		}
	}

	if (inFile3.size() != 0) {
		if (polygonList3.size() > 4000) {
			//cout << "< 4000" << endl;
			for (int i = 0; i < 3000; i++) {
				xpm = fillPolygon(polygonList3[i], xpm);

			}
		}
		else {
			for (int i = 0; i < polygonList3.size(); i++) {
				xpm = fillPolygon(polygonList3[i], xpm);

			}
		}
	}



	

	//cout << "hello2";
	if (inFile.size() != 0) {
		zbufferxpm(polygonList);
	}
	if (inFile2.size() != 0) {
		zbufferxpm2(polygonList2);
	}
	if (inFile3.size() != 0) {
		zbufferxpm3(polygonList3);
	}

	


	ofstream myfile("example.xpm");

	for (int i = 0; i < xpm.size(); i++) {
		myfile << xpm[i];
	}
	xpm[69][0] = '/';
	for (int i = 0; i < xpm.size(); i++) {
		cout << xpm[i];
	}
	
}

vector<string> setUpXPM(vector<string> inputXPM) {
	//red
	inputXPM.push_back("/* XPM */\n");
	inputXPM.push_back("static char *sco100[] = {\n");
	inputXPM.push_back("/* width height num_colors chars_per_pixel */\n");
	inputXPM.push_back("\"500 500 64 1\",\n");
	inputXPM.push_back("/* colors */\n"); 
	inputXPM.push_back("\"j c #ffffff\",\n");
	inputXPM.push_back("\"i c #ffe6e6\",\n");
	inputXPM.push_back("\"h c #ffcccc\",\n");
	inputXPM.push_back("\"g c #ffb3b3\",\n");
	inputXPM.push_back("\"f c #ff9999\",\n");
	inputXPM.push_back("\"e c #ff8080\",\n"); // lighter side
	inputXPM.push_back("\"d c #ff6666\",\n"); // lighter side
	inputXPM.push_back("\"c c #ff4d4d\",\n"); // lighter side
	inputXPM.push_back("\"b c #ff3333\",\n"); // lighter side
	inputXPM.push_back("\"a c #ff1a1a\",\n"); // lighter side
	inputXPM.push_back("\"x c #ff0000\",\n"); //base red
	inputXPM.push_back("\"k c #e60000\",\n");
	inputXPM.push_back("\"l c #cc0000\",\n");
	inputXPM.push_back("\"m c #b30000\",\n");
	inputXPM.push_back("\"n c #990000\",\n");
	inputXPM.push_back("\"o c #660000\",\n"); 
	inputXPM.push_back("\"p c #4d0000\",\n"); 
	inputXPM.push_back("\"q c #330000\",\n"); 
	inputXPM.push_back("\"r c #1a0000\",\n"); 
	inputXPM.push_back("\"s c #000000\",\n"); 
	inputXPM.push_back("\"t c #800000\",\n"); // darker side
	inputXPM.push_back("\"- c #000000\",\n");
	/////green
	inputXPM.push_back("\"A c #ffffff\",\n");
	inputXPM.push_back("\"B c #e6ffe6\",\n");
	inputXPM.push_back("\"C c #ccffcc\",\n");
	inputXPM.push_back("\"D c #b3ffb3\",\n");
	inputXPM.push_back("\"E c #99ff99\",\n");
	inputXPM.push_back("\"F c #80ff80\",\n"); // lighter side
	inputXPM.push_back("\"G c #66ff66\",\n"); // lighter side
	inputXPM.push_back("\"H c #4dff4d\",\n"); // lighter side
	inputXPM.push_back("\"I c #33ff33\",\n"); // lighter side
	inputXPM.push_back("\"J c #1aff1a\",\n"); // lighter side
	inputXPM.push_back("\"K c #00ff00\",\n"); 
	inputXPM.push_back("\"L c #00e600\",\n");
	inputXPM.push_back("\"M c #00cc00\",\n");
	inputXPM.push_back("\"N c #00b300\",\n");
	inputXPM.push_back("\"O c #009900\",\n");
	inputXPM.push_back("\"P c #008000\",\n");
	inputXPM.push_back("\"Q c #006600\",\n");
	inputXPM.push_back("\"R c #004d00\",\n");
	inputXPM.push_back("\"S c #003300\",\n");
	inputXPM.push_back("\"T c #001a00\",\n");
	inputXPM.push_back("\"U c #000000\",\n"); // darker side
	//blue
	inputXPM.push_back("\"1 c #ffffff\",\n");
	inputXPM.push_back("\"2 c #e6e6ff\",\n");
	inputXPM.push_back("\"3 c #ccccff\",\n");
	inputXPM.push_back("\"4 c #b3b3ff\",\n");
	inputXPM.push_back("\"5 c #9999ff\",\n");
	inputXPM.push_back("\"6 c #8080ff\",\n"); // lighter side
	inputXPM.push_back("\"7 c #6666ff\",\n"); // lighter side
	inputXPM.push_back("\"8 c #4d4dff\",\n"); // lighter side
	inputXPM.push_back("\"9 c #3333ff\",\n"); // lighter side
	inputXPM.push_back("\"0 c #1a1aff\",\n"); // lighter side
	inputXPM.push_back("\"! c #0000ff\",\n");
	inputXPM.push_back("\"# c #0000e6\",\n");
	inputXPM.push_back("\"$ c #0000cc\",\n");
	inputXPM.push_back("\"% c #0000b3\",\n");
	inputXPM.push_back("\"^ c #000099\",\n");
	inputXPM.push_back("\"& c #000080\",\n");
	inputXPM.push_back("\"* c #000066\",\n");
	inputXPM.push_back("\"( c #00004d\",\n");
	inputXPM.push_back("\") c #000033\",\n");
	inputXPM.push_back("\"= c #00001a\",\n");
	inputXPM.push_back("\"+ c #000000\"\n"); // 



	inputXPM.push_back("/* pixels */\n");
	string whiteBackground(500, '-');

	int k = 0;
	while (k < 500) {
		if (k != 499) {
			inputXPM.push_back("\"" + whiteBackground + "\",\n");
			k++;
		}

		if (k == 499) {
			inputXPM.push_back("\"" + whiteBackground + "\"\n");
			k++;
		}

	}
	inputXPM.push_back("};");

	

	return inputXPM;
}

vector<string> setUpZBuffer(vector<string> inputZBuffer) {
	inputZBuffer.push_back("/* XPM */\n");
	inputZBuffer.push_back("static char *sco100[] = {\n");
	inputZBuffer.push_back("/* width height num_colors chars_per_pixel */\n");
	inputZBuffer.push_back("\"500 500 2 1\",\n");
	inputZBuffer.push_back("/* colors */\n");
	inputZBuffer.push_back("\"X c #010101\",\n");
	inputZBuffer.push_back("\"-  c #ffffff\",\n");
	inputZBuffer.push_back("/* pixels */\n");

	string whiteBackground(500, '-');

	int k = 0;
	while (k < 500) {
		if (k != 499) {
			inputZBuffer.push_back("\"" + whiteBackground + "\",\n");
			k++;
		}

		if (k == 499) {
			inputZBuffer.push_back("\"" + whiteBackground + "\"\n");
			k++;
		}

	}
	inputZBuffer.push_back("};");



	return inputZBuffer;
}



void writeXPM(vector<string> inputXPM) {
	ofstream myfile("output.xpm");
	for (int i = 0; i < inputXPM.size(); i++) {
		myfile << inputXPM[i];
	}
}

void writeZBuffer(vector<string> inputXPM) {
	ofstream myfile("zbuffer.txt");
	for (int i = 0; i < inputXPM.size(); i++) {
		myfile << inputXPM[i];
	}
}

vector <Face*> createFaceList(string inFile) {
	string line;
	vector<Vertice*> verticeList;
	vector<Face*> faceList;

	ifstream File(inFile.c_str());
	while (!File.eof()) {

		getline(File, line);

		if (line[0] == 'v') {
			vector<string> temp;

			istringstream iss(line);

			for (string line; iss >> line; ) {
				temp.push_back(line);
			}

			float x = stof(temp[1]);
			float y = stof(temp[2]);
			float z = stof(temp[3]);


			Vertice* newVertice = new Vertice(x, y, z);
			verticeList.push_back(newVertice);

		}

		else if (line[0] == 'f') {

			vector<string> temp;
			vector<Vertice*> temp2;

			istringstream iss(line);

			for (string line; iss >> line; ) {
				temp.push_back(line);
			}

			int vert1 = atoi(temp[1].c_str());
			int vert2 = atoi(temp[2].c_str());
			int vert3 = atoi(temp[3].c_str());

			vert1--;
			vert2--;
			vert3--;

			temp2.push_back(verticeList[vert1]);
			temp2.push_back(verticeList[vert2]);
			temp2.push_back(verticeList[vert3]);

			//cout << vert1+1 << " " << vert2+1 << " " << vert3+1 << endl;

			Face* newFace = new Face(temp2);
			faceList.push_back(newFace);

		}

	}
	return faceList;
}

vector <Polygon*> createPolygonList(vector<Face*> faceList) {
	vector<Polygon*> polygonList;

	for (int i = 0; i < faceList.size(); i++) {
		Polygon* newPolygon = new Polygon(faceList[i]);
		polygonList.push_back(newPolygon);
	}

	return polygonList;
}

void calculateViewMatrix()
{
	float rotationMatrix[4][4];
	float translationMatrix[4][4];

	float VUPMagnitude = sqrt((VUPX*VUPX) + (VUPY*VUPY) + (VUPZ*VUPZ));
	float VPNMagnitude = sqrt((VPNX*VPNX) + (VPNY*VPNY) + (VPNZ*VPNZ));

	VUPX = VUPX / VUPMagnitude;
	VUPY=  VUPY / VUPMagnitude;
	VUPZ=  VUPZ / VUPMagnitude;

	VPNX = VPNX / VPNMagnitude;
	VPNY = VPNY / VPNMagnitude;
	VPNZ = VPNZ / VPNMagnitude;

	float ux = ((VUPY*VPNZ) - (VUPZ*VPNY));
	float uy = ((VUPZ*VPNX) - (VUPX*VPNZ));
	float uz = ((VUPX*VPNY) - (VUPY*VPNX));

	float nx = VPNX;
	float ny = VPNY;
	float nz = VPNZ;

	//n x u
	float vx = ((ny*uz)) - ((nz*uy));
	float vy = ((nz*ux)) - ((nx*uz));
	float vz = ((nx*uy)) - ((ny*ux));

	rotationMatrix[0][0] = ux;
	rotationMatrix[0][1] = vx;
	rotationMatrix[0][2] = nx;
	rotationMatrix[0][3] = 0.0;

	rotationMatrix[1][0] = uy;
	rotationMatrix[1][1] = vy;
	rotationMatrix[1][2] = ny;
	rotationMatrix[1][3] = 0.0;

	rotationMatrix[2][0] = uz;
	rotationMatrix[2][1] = vz;
	rotationMatrix[2][2] = nz;
	rotationMatrix[2][3] = 0.0;

	rotationMatrix[3][0] = 0.0;
	rotationMatrix[3][1] = 0.0;
	rotationMatrix[3][2] = 0.0;
	rotationMatrix[3][3] = 1.0;

	translationMatrix[0][0] = 1.0;
	translationMatrix[0][1] = 0.0;
	translationMatrix[0][2] = 0.0;
	translationMatrix[0][3] = 0.0;

	translationMatrix[1][0] = 0.0;
	translationMatrix[1][1] = 1.0;
	translationMatrix[1][2] = 0.0;
	translationMatrix[1][3] = 0.0;

	translationMatrix[2][0] = 0.0;
	translationMatrix[2][1] = 0.0;
	translationMatrix[2][2] = 1.0;
	translationMatrix[2][3] = 0.0;

	translationMatrix[3][0] = -VRPX;
	translationMatrix[3][1] = -VRPY;
	translationMatrix[3][2] = -VRPZ;
	translationMatrix[3][3] = 1.0;

	viewMatrix[0][0] = rotationMatrix[0][0] * translationMatrix[0][0] + rotationMatrix[1][0] * translationMatrix[0][1] + rotationMatrix[2][0] * translationMatrix[0][2] + rotationMatrix[3][0] * translationMatrix[0][3];
	viewMatrix[0][1] = rotationMatrix[0][1] * translationMatrix[0][0] + rotationMatrix[1][1] * translationMatrix[0][1] + rotationMatrix[2][1] * translationMatrix[0][2] + rotationMatrix[3][1] * translationMatrix[0][3];
	viewMatrix[0][2] = rotationMatrix[0][2] * translationMatrix[0][0] + rotationMatrix[1][2] * translationMatrix[0][1] + rotationMatrix[2][2] * translationMatrix[0][2] + rotationMatrix[3][2] * translationMatrix[0][3];
	viewMatrix[0][3] = rotationMatrix[0][3] * translationMatrix[0][0] + rotationMatrix[1][3] * translationMatrix[0][1] + rotationMatrix[2][3] * translationMatrix[0][2] + rotationMatrix[3][3] * translationMatrix[0][3];

	viewMatrix[1][0] = rotationMatrix[0][0] * translationMatrix[1][0] + rotationMatrix[1][0] * translationMatrix[1][1] + rotationMatrix[2][0] * translationMatrix[1][2] + rotationMatrix[3][0] * translationMatrix[1][3];
	viewMatrix[1][1] = rotationMatrix[0][1] * translationMatrix[1][0] + rotationMatrix[1][1] * translationMatrix[1][1] + rotationMatrix[2][1] * translationMatrix[1][2] + rotationMatrix[3][1] * translationMatrix[1][3];
	viewMatrix[1][2] = rotationMatrix[0][2] * translationMatrix[1][0] + rotationMatrix[1][2] * translationMatrix[1][1] + rotationMatrix[2][2] * translationMatrix[1][2] + rotationMatrix[3][2] * translationMatrix[1][3];
	viewMatrix[1][3] = rotationMatrix[0][3] * translationMatrix[1][0] + rotationMatrix[1][3] * translationMatrix[1][1] + rotationMatrix[2][3] * translationMatrix[1][2] + rotationMatrix[3][3] * translationMatrix[1][3];

	viewMatrix[2][0] = rotationMatrix[0][0] * translationMatrix[2][0] + rotationMatrix[1][0] * translationMatrix[2][1] + rotationMatrix[2][0] * translationMatrix[2][2] + rotationMatrix[3][0] * translationMatrix[2][3];
	viewMatrix[2][1] = rotationMatrix[0][1] * translationMatrix[2][0] + rotationMatrix[1][1] * translationMatrix[2][1] + rotationMatrix[2][1] * translationMatrix[2][2] + rotationMatrix[3][1] * translationMatrix[2][3];
	viewMatrix[2][2] = rotationMatrix[0][2] * translationMatrix[2][0] + rotationMatrix[1][2] * translationMatrix[2][1] + rotationMatrix[2][2] * translationMatrix[2][2] + rotationMatrix[3][2] * translationMatrix[2][3];
	viewMatrix[2][3] = rotationMatrix[0][3] * translationMatrix[2][0] + rotationMatrix[1][3] * translationMatrix[2][1] + rotationMatrix[2][3] * translationMatrix[2][2] + rotationMatrix[3][3] * translationMatrix[2][3];

	viewMatrix[3][0] = rotationMatrix[0][0] * translationMatrix[3][0] + rotationMatrix[1][0] * translationMatrix[3][1] + rotationMatrix[2][0] * translationMatrix[3][2] + rotationMatrix[3][0] * translationMatrix[3][3];
	viewMatrix[3][1] = rotationMatrix[0][1] * translationMatrix[3][0] + rotationMatrix[1][1] * translationMatrix[3][1] + rotationMatrix[2][1] * translationMatrix[3][2] + rotationMatrix[3][1] * translationMatrix[3][3];
	viewMatrix[3][2] = rotationMatrix[0][2] * translationMatrix[3][0] + rotationMatrix[1][2] * translationMatrix[3][1] + rotationMatrix[2][2] * translationMatrix[3][2] + rotationMatrix[3][2] * translationMatrix[3][3];
	viewMatrix[3][3] = rotationMatrix[0][3] * translationMatrix[3][0] + rotationMatrix[1][3] * translationMatrix[3][1] + rotationMatrix[2][3] * translationMatrix[3][2] + rotationMatrix[3][3] * translationMatrix[3][3];
}

void calculatePerspectiveProjectionMatrix()
{

	projectionMatrix[0][0] = (2 * PRPZ) / ((VRCUpperU - VRCLowerU) * (PRPZ - back));
	projectionMatrix[0][1] = 0.0;
	projectionMatrix[0][2] = 0.0;
	projectionMatrix[0][3] = 0.0;

	projectionMatrix[1][0] = 0.0;
	projectionMatrix[1][1] = (2 * PRPZ) / ((VRCUpperV - VRCLowerV) * (PRPZ - back));
	projectionMatrix[1][2] = 0.0;
	projectionMatrix[1][3] = 0.0;

	projectionMatrix[2][0] = ((VRCUpperU + VRCLowerU) - 2*PRPX) / ((VRCUpperU - VRCLowerU)*(PRPZ - back));
	projectionMatrix[2][1] = ((VRCUpperV + VRCLowerV) - 2 * PRPY) / ((VRCUpperV - VRCLowerV)*(PRPZ - back));
	projectionMatrix[2][2] = 1.0 / (PRPZ - back);
	projectionMatrix[2][3] = 0.0;

	projectionMatrix[3][0] = -((VRCUpperU + VRCLowerU) * PRPZ) / ((VRCUpperU - VRCLowerU)*(PRPZ - back));
	projectionMatrix[3][1] = -((VRCUpperV + VRCLowerV) * PRPZ) / ((VRCUpperV - VRCLowerV)*(PRPZ - back));
	projectionMatrix[3][2] = -((PRPZ) / (PRPZ - back));
	projectionMatrix[3][3] = 1.0;
}

void calculateParallelProjectionMatrix() {

	projectionMatrix[0][0] = 2 / (VRCUpperU - VRCLowerU);
	projectionMatrix[0][1] = 0.0;
	projectionMatrix[0][2] = 0.0;
	projectionMatrix[0][3] = 0.0;

	projectionMatrix[1][0] = 0.0;
	projectionMatrix[1][1] = 2 / (VRCUpperV - VRCLowerV);
	projectionMatrix[1][2] = 0.0;
	projectionMatrix[1][3] = 0.0;

	projectionMatrix[2][0] = ((VRCUpperU + VRCLowerU) - 2 * PRPX) / ((VRCUpperU - VRCLowerU)*(PRPZ));
	projectionMatrix[2][1] = ((VRCUpperV + VRCLowerV) - 2 * PRPY) / ((VRCUpperV - VRCLowerV)*(PRPZ));
	projectionMatrix[2][2] = 1.0 / (front - back);
	projectionMatrix[2][3] = 0.0;

	projectionMatrix[3][0] = -((VRCUpperU + VRCLowerU)) / ((VRCUpperU - VRCLowerU));
	projectionMatrix[3][1] = -((VRCUpperV + VRCLowerV)) / ((VRCUpperV - VRCLowerV));
	projectionMatrix[3][2] = -((front) / (front - back));
	projectionMatrix[3][3] = 1.0;

}

void calculateFinalMatrix() {

	finalMatrix[0][0] = projectionMatrix[0][0] * viewMatrix[0][0] + projectionMatrix[1][0] * viewMatrix[0][1] + projectionMatrix[2][0] * viewMatrix[0][2] + projectionMatrix[3][0] * viewMatrix[0][3];
	finalMatrix[0][1] = projectionMatrix[0][1] * viewMatrix[0][0] + projectionMatrix[1][1] * viewMatrix[0][1] + projectionMatrix[2][1] * viewMatrix[0][2] + projectionMatrix[3][1] * viewMatrix[0][3];
	finalMatrix[0][2] = projectionMatrix[0][2] * viewMatrix[0][0] + projectionMatrix[1][2] * viewMatrix[0][1] + projectionMatrix[2][2] * viewMatrix[0][2] + projectionMatrix[3][2] * viewMatrix[0][3];
	finalMatrix[0][3] = projectionMatrix[0][3] * viewMatrix[0][0] + projectionMatrix[1][3] * viewMatrix[0][1] + projectionMatrix[2][3] * viewMatrix[0][2] + projectionMatrix[3][3] * viewMatrix[0][3];

	finalMatrix[1][0] = projectionMatrix[0][0] * viewMatrix[1][0] + projectionMatrix[1][0] * viewMatrix[1][1] + projectionMatrix[2][0] * viewMatrix[1][2] + projectionMatrix[3][0] * viewMatrix[1][3];
	finalMatrix[1][1] = projectionMatrix[0][1] * viewMatrix[1][0] + projectionMatrix[1][1] * viewMatrix[1][1] + projectionMatrix[2][1] * viewMatrix[1][2] + projectionMatrix[3][1] * viewMatrix[1][3];
	finalMatrix[1][2] = projectionMatrix[0][2] * viewMatrix[1][0] + projectionMatrix[1][2] * viewMatrix[1][1] + projectionMatrix[2][2] * viewMatrix[1][2] + projectionMatrix[3][2] * viewMatrix[1][3];
	finalMatrix[1][3] = projectionMatrix[0][3] * viewMatrix[1][0] + projectionMatrix[1][3] * viewMatrix[1][1] + projectionMatrix[2][3] * viewMatrix[1][2] + projectionMatrix[3][3] * viewMatrix[1][3];

	finalMatrix[2][0] = projectionMatrix[0][0] * viewMatrix[2][0] + projectionMatrix[1][0] * viewMatrix[2][1] + projectionMatrix[2][0] * viewMatrix[2][2] + projectionMatrix[3][0] * viewMatrix[2][3];
	finalMatrix[2][1] = projectionMatrix[0][1] * viewMatrix[2][0] + projectionMatrix[1][1] * viewMatrix[2][1] + projectionMatrix[2][1] * viewMatrix[2][2] + projectionMatrix[3][1] * viewMatrix[2][3];
	finalMatrix[2][2] = projectionMatrix[0][2] * viewMatrix[2][0] + projectionMatrix[1][2] * viewMatrix[2][1] + projectionMatrix[2][2] * viewMatrix[2][2] + projectionMatrix[3][2] * viewMatrix[2][3];
	finalMatrix[2][3] = projectionMatrix[0][3] * viewMatrix[2][0] + projectionMatrix[1][3] * viewMatrix[2][1] + projectionMatrix[2][3] * viewMatrix[2][2] + projectionMatrix[3][3] * viewMatrix[2][3];

	

	finalMatrix[3][0] = projectionMatrix[0][0] * viewMatrix[3][0] + projectionMatrix[1][0] * viewMatrix[3][1] + projectionMatrix[2][0] * viewMatrix[3][2] + projectionMatrix[3][0] * viewMatrix[3][3];
	finalMatrix[3][1] = projectionMatrix[0][1] * viewMatrix[3][0] + projectionMatrix[1][1] * viewMatrix[3][1] + projectionMatrix[2][1] * viewMatrix[3][2] + projectionMatrix[3][1] * viewMatrix[3][3];
	finalMatrix[3][2] = projectionMatrix[0][2] * viewMatrix[3][0] + projectionMatrix[1][2] * viewMatrix[3][1] + projectionMatrix[2][2] * viewMatrix[3][2] + projectionMatrix[3][2] * viewMatrix[3][3];
	finalMatrix[3][3] = projectionMatrix[0][3] * viewMatrix[3][0] + projectionMatrix[1][3] * viewMatrix[3][1] + projectionMatrix[2][3] * viewMatrix[3][2] + projectionMatrix[3][3] * viewMatrix[3][3];

}

vector <Polygon*> updatePolygons(vector <Polygon*> polygonList)
{
	float homogenousCoordinate[4][1];
	float homogenousCoordinate2[4][1];

	float homogenousCoordinatesResult[4][1];
	float homogenousCoordinatesResult2[4][1];



	for (int i = 0; i < polygonList.size(); i++) {
		for (int m = 0; m < polygonList[i]->polyLines.size(); m++) {

			homogenousCoordinate[0][0] = polygonList[i]->polyLines[m]->x1;
			homogenousCoordinate[0][1] = polygonList[i]->polyLines[m]->y1;
			homogenousCoordinate[0][2] = polygonList[i]->polyLines[m]->z1;
			homogenousCoordinate[0][3] = 1;

			homogenousCoordinate2[0][0] = polygonList[i]->polyLines[m]->x2;
			homogenousCoordinate2[0][1] = polygonList[i]->polyLines[m]->y2;
			homogenousCoordinate2[0][2] = polygonList[i]->polyLines[m]->z2;
			homogenousCoordinate2[0][3] = 1;


			homogenousCoordinatesResult[0][0] = finalMatrix[0][0] * homogenousCoordinate[0][0] + finalMatrix[1][0] * homogenousCoordinate[0][1] + finalMatrix[2][0] * homogenousCoordinate[0][2] + finalMatrix[3][0] * homogenousCoordinate[0][3];
			homogenousCoordinatesResult[0][1] = finalMatrix[0][1] * homogenousCoordinate[0][0] + finalMatrix[1][1] * homogenousCoordinate[0][1] + finalMatrix[2][1] * homogenousCoordinate[0][2] + finalMatrix[3][1] * homogenousCoordinate[0][3];
			homogenousCoordinatesResult[0][2] = finalMatrix[0][2] * homogenousCoordinate[0][0] + finalMatrix[1][2] * homogenousCoordinate[0][1] + finalMatrix[2][2] * homogenousCoordinate[0][2] + finalMatrix[3][2] * homogenousCoordinate[0][3];
			homogenousCoordinatesResult[0][3] = finalMatrix[0][3] * homogenousCoordinate[0][0] + finalMatrix[1][3] * homogenousCoordinate[0][1] + finalMatrix[2][3] * homogenousCoordinate[0][2] + finalMatrix[3][3] * homogenousCoordinate[0][3];

			homogenousCoordinatesResult2[0][0] = finalMatrix[0][0] * homogenousCoordinate2[0][0] + finalMatrix[1][0] * homogenousCoordinate2[0][1] + finalMatrix[2][0] * homogenousCoordinate2[0][2] + finalMatrix[3][0] * homogenousCoordinate2[0][3];
			homogenousCoordinatesResult2[0][1] = finalMatrix[0][1] * homogenousCoordinate2[0][0] + finalMatrix[1][1] * homogenousCoordinate2[0][1] + finalMatrix[2][1] * homogenousCoordinate2[0][2] + finalMatrix[3][1] * homogenousCoordinate2[0][3];
			homogenousCoordinatesResult2[0][2] = finalMatrix[0][2] * homogenousCoordinate2[0][0] + finalMatrix[1][2] * homogenousCoordinate2[0][1] + finalMatrix[2][2] * homogenousCoordinate2[0][2] + finalMatrix[3][2] * homogenousCoordinate2[0][3];
			homogenousCoordinatesResult2[0][3] = finalMatrix[0][3] * homogenousCoordinate2[0][0] + finalMatrix[1][3] * homogenousCoordinate2[0][1] + finalMatrix[2][3] * homogenousCoordinate2[0][2] + finalMatrix[3][3] * homogenousCoordinate2[0][3];


			polygonList[i]->polyLines[m]->x1 = homogenousCoordinatesResult[0][0];
			polygonList[i]->polyLines[m]->y1 = homogenousCoordinatesResult[0][1];
			polygonList[i]->polyLines[m]->z1 = homogenousCoordinatesResult[0][2];

			polygonList[i]->polyLines[m]->x2 = homogenousCoordinatesResult2[0][0];
			polygonList[i]->polyLines[m]->y2 = homogenousCoordinatesResult2[0][1];
			polygonList[i]->polyLines[m]->z2 = homogenousCoordinatesResult2[0][2];
	
	}
	}

	return polygonList;
}

vector <Polygon*> clipping(vector <Polygon*> polygonList){

	if (parallelProjection == true) {
		vector <Polygon*> newPolygons;
		for (int i = 0; i < polygonList.size(); i++) {
			int counter = 0;
			for (int k = 0; k < polygonList[i]->polyLines.size(); k++) {
				if (polygonList[i]->polyLines[k]->y1 > 1) {
					//cout << "Point Above View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->y1 < -1) {
					//cout << "Point Below View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->x1 > 1) {
					//cout << "Point Right Of View Volume" << endl;
					counter++;
				}

				if (polygonList[i]->polyLines[k]->x1 < -1) {
					//cout << "Point Left Of View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->z1 > 0) {
					//cout << "Point Infront Of View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->z1 < -1) {
					//cout << "Point Behind View Volume" << endl;
					counter++;
				}

				if (polygonList[i]->polyLines[k]->y2 > 1) {
					//cout << "Point Above View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->y2 < -1) {
					//cout << "Point Below View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->x2 > 1) {
					//cout << "Point Right Of View Volume" << endl;
					counter++;
				}

				if (polygonList[i]->polyLines[k]->x2 < -1) {
					//cout << "Point Left Of View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->z2 > 0) {
					//cout << "Point Infront Of View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->z2 < -1) {
					//cout << "Point Behind View Volume" << endl;
					counter++;
				}
			}
			if (counter == 0) {
				//cout << "FULLY INSIDE VIEWING VOLUME" << endl;
				newPolygons.push_back(polygonList[i]);

			}

			else {
				//cout << "PARTIALLY OR FULLY OUTSIDE VIEWING VOLUME, REJECTED" << endl;
			}
		}
	}

	else {
		vector <Polygon*> newPolygons;
		for (int i = 0; i < polygonList.size(); i++) {
			int counter = 0;
			float zmin = (PRPZ - front) / (back - PRPZ);
			for (int k = 0; k < polygonList[i]->polyLines.size(); k++) {
				if (polygonList[i]->polyLines[k]->y1 > -(polygonList[i]->polyLines[k]->z1)) {
					//cout << "Point Above View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->y1 < (polygonList[i]->polyLines[k]->z1)) {
					//cout << "Point Below View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->x1 > -(polygonList[i]->polyLines[k]->z1)) {
					//cout << "Point Right Of View Volume" << endl;
					counter++;
				}

				if (polygonList[i]->polyLines[k]->x1 < (polygonList[i]->polyLines[k]->z1)) {
					//cout << "Point Left Of View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->z1 > zmin) {
					//cout << "Point Infront Of View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->z1 < -1) {
					//cout << "Point Behind View Volume" << endl;
					counter++;
				}

				if (polygonList[i]->polyLines[k]->y2 > -(polygonList[i]->polyLines[k]->z2)) {
					//cout << "Point Above View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->y2 < (polygonList[i]->polyLines[k]->z2)) {
					//cout << "Point Below View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->x2 > -(polygonList[i]->polyLines[k]->z2)) {
					//cout << "Point Right Of View Volume" << endl;
					counter++;
				}

				if (polygonList[i]->polyLines[k]->x2 < (polygonList[i]->polyLines[k]->z2)) {
					//cout << "Point Left Of View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->z2 > zmin) {
					//cout << "Point Infront Of View Volume" << endl;
					counter++;
				}
				if (polygonList[i]->polyLines[k]->z2 < -1) {
					//cout << "Point Behind View Volume" << endl;
					counter++;
				}
			}
			if (counter == 0) {
				//cout << "FULLY INSIDE VIEWING VOLUME" << endl;
				newPolygons.push_back(polygonList[i]);

			}

			else {
				//cout << "PARTIALLY OR FULLY OUTSIDE VIEWING VOLUME, REJECTED" << endl;
			}
		}

	}

	return newPolygons;
}

vector <Polygon*>  projectTo2d(vector <Polygon*> newPolygons)
{
	if (parallelProjection == false) {
		for (int i = 0; i < newPolygons.size(); i++){

			for (int k = 0; k < newPolygons[i]->polyLines.size(); k++) {
				newPolygons[i]->polyLines[k]->x1 = newPolygons[i]->polyLines[k]->x1 / -(newPolygons[i]->polyLines[k]->z1);
				newPolygons[i]->polyLines[k]->y1 = newPolygons[i]->polyLines[k]->y1 / -(newPolygons[i]->polyLines[k]->z1);
				
				newPolygons[i]->polyLines[k]->x2 = newPolygons[i]->polyLines[k]->x2 / -(newPolygons[i]->polyLines[k]->z2);
				newPolygons[i]->polyLines[k]->y2 = newPolygons[i]->polyLines[k]->y2 / -(newPolygons[i]->polyLines[k]->z2);					
			}
		}
	}

	return newPolygons;
}

vector<Polygon*> convertToViewPort(vector<Polygon*> newPolygons)
{
	float homogenousCoordinate[3][1];
	float homogenousCoordinate2[3][1];
	float homogenousCoordinatesResult[3][1];
	float homogenousCoordinatesResult2[3][1];

	

	float translate1[3][3];
	float translate2[3][3];
	float scale[3][3];
	float translate1scale[3][3];
	float finalViewPortMatrix[3][3];

	translate1[0][0] = 1;
	translate1[0][1] = 0;
	translate1[0][2] = 0;

	translate1[1][0] = 0;
	translate1[1][1] = 1;
	translate1[1][2] = 0;

	translate1[2][0] = viewportLowerX;
	translate1[2][1] = viewportLowerY;
	translate1[2][2] = 1;

	translate2[0][0] = 1;
	translate2[0][1] = 0;
	translate2[0][2] = 0;

	translate2[1][0] = 0;
	translate2[1][1] = 1;
	translate2[1][2] = 0;

	translate2[2][0] = -(-1);
	translate2[2][1] = -(-1);
	translate2[2][2] = 1;

	scale[0][0] = (viewportUpperX - viewportLowerX) / (1 - (-1));
	scale[0][1] = 0;
	scale[0][2] = 0;

	scale[1][0] = 0;
	scale[1][1] = (viewPortUpperY - viewportLowerY) / (1 - (-1));
	scale[1][2] = 0;

	scale[2][0] = 0;
	scale[2][1] = 0;
	scale[2][2] = 1;



	translate1scale[0][0] = translate1[0][0] * scale[0][0] + translate1[1][0] * scale[0][1] + translate1[2][0] * scale[0][2];
	translate1scale[0][1] = translate1[0][1] * scale[0][0] + translate1[1][1] * scale[0][1] + translate1[2][1] * scale[0][2];
	translate1scale[0][2] = translate1[0][2] * scale[0][0] + translate1[1][2] * scale[0][1] + translate1[2][2] * scale[0][2];
	

	translate1scale[1][0] = translate1[0][0] * scale[1][0] + translate1[1][0] * scale[1][1] + translate1[2][0] * scale[1][2];
	translate1scale[1][1] = translate1[0][1] * scale[1][0] + translate1[1][1] * scale[1][1] + translate1[2][1] * scale[1][2];
	translate1scale[1][2] = translate1[0][2] * scale[1][0] + translate1[1][2] * scale[1][1] + translate1[2][2] * scale[1][2];
	

	translate1scale[2][0] = translate1[0][0] * scale[2][0] + translate1[1][0] * scale[2][1] + translate1[2][0] * scale[2][2];
	translate1scale[2][1] = translate1[0][1] * scale[2][0] + translate1[1][1] * scale[2][1] + translate1[2][1] * scale[2][2];
	translate1scale[2][2] = translate1[0][2] * scale[2][0] + translate1[1][2] * scale[2][1] + translate1[2][2] * scale[2][2];

	finalViewPortMatrix[0][0] = translate1scale[0][0] * translate2[0][0] + translate1scale[1][0] * translate2[0][1] + translate1scale[2][0] * translate2[0][2];
	finalViewPortMatrix[0][1] = translate1scale[0][1] * translate2[0][0] + translate1scale[1][1] * translate2[0][1] + translate1scale[2][1] * translate2[0][2];
	finalViewPortMatrix[0][2] = translate1scale[0][2] * translate2[0][0] + translate1scale[1][2] * translate2[0][1] + translate1scale[2][2] * translate2[0][2];


	finalViewPortMatrix[1][0] = translate1scale[0][0] * translate2[1][0] + translate1scale[1][0] * translate2[1][1] + translate1scale[2][0] * translate2[1][2];
	finalViewPortMatrix[1][1] = translate1scale[0][1] * translate2[1][0] + translate1scale[1][1] * translate2[1][1] + translate1scale[2][1] * translate2[1][2];
	finalViewPortMatrix[1][2] = translate1scale[0][2] * translate2[1][0] + translate1scale[1][2] * translate2[1][1] + translate1scale[2][2] * translate2[1][2];


	finalViewPortMatrix[2][0] = translate1scale[0][0] * translate2[2][0] + translate1scale[1][0] * translate2[2][1] + translate1scale[2][0] * translate2[2][2];
	finalViewPortMatrix[2][1] = translate1scale[0][1] * translate2[2][0] + translate1scale[1][1] * translate2[2][1] + translate1scale[2][1] * translate2[2][2];
	finalViewPortMatrix[2][2] = translate1scale[0][2] * translate2[2][0] + translate1scale[1][2] * translate2[2][1] + translate1scale[2][2] * translate2[2][2];
	

	for (int i = 0; i < newPolygons.size(); i++) {
		for (int k = 0; k < newPolygons[i]->polyLines.size(); k++) {

			homogenousCoordinate[0][0] = newPolygons[i]->polyLines[k]->x1;
			homogenousCoordinate[0][1] = newPolygons[i]->polyLines[k]->y1;
			homogenousCoordinate[0][2] = 1;

			homogenousCoordinate2[0][0] = newPolygons[i]->polyLines[k]->x2;
			homogenousCoordinate2[0][1] = newPolygons[i]->polyLines[k]->y2;
			homogenousCoordinate2[0][2] = 1;

			homogenousCoordinatesResult[0][0] = finalViewPortMatrix[0][0] * homogenousCoordinate[0][0] + finalViewPortMatrix[1][0] * homogenousCoordinate[0][1] + finalViewPortMatrix[2][0] * homogenousCoordinate[0][2];
			homogenousCoordinatesResult[0][1] = finalViewPortMatrix[0][1] * homogenousCoordinate[0][0] + finalViewPortMatrix[1][1] * homogenousCoordinate[0][1] + finalViewPortMatrix[2][1] * homogenousCoordinate[0][2];
			homogenousCoordinatesResult[0][2] = finalViewPortMatrix[0][2] * homogenousCoordinate[0][0] + finalViewPortMatrix[1][2] * homogenousCoordinate[0][1] + finalViewPortMatrix[2][2] * homogenousCoordinate[0][2];
			

			homogenousCoordinatesResult2[0][0] = finalViewPortMatrix[0][0] * homogenousCoordinate2[0][0] + finalViewPortMatrix[1][0] * homogenousCoordinate2[0][1] + finalViewPortMatrix[2][0] * homogenousCoordinate2[0][2];
			homogenousCoordinatesResult2[0][1] = finalViewPortMatrix[0][1] * homogenousCoordinate2[0][0] + finalViewPortMatrix[1][1] * homogenousCoordinate2[0][1] + finalViewPortMatrix[2][1] * homogenousCoordinate2[0][2];
			homogenousCoordinatesResult2[0][2] = finalViewPortMatrix[0][2] * homogenousCoordinate2[0][0] + finalViewPortMatrix[1][2] * homogenousCoordinate2[0][1] + finalViewPortMatrix[2][2] * homogenousCoordinate2[0][2];

			

			newPolygons[i]->polyLines[k]->x1 = homogenousCoordinatesResult[0][0];
			newPolygons[i]->polyLines[k]->y1 = homogenousCoordinatesResult[0][1];
	

			newPolygons[i]->polyLines[k]->x2 = homogenousCoordinatesResult2[0][0];
			newPolygons[i]->polyLines[k]->y2 = homogenousCoordinatesResult2[0][1];
		}
	}

	return newPolygons;
}

vector<string> printXPM(Polygon* polygon) {
	for (int i = 0; i < polygon->polyLines.size(); i++) {
		Line* tempLine = polygon->polyLines[i];

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
				if ((x1) != 0  && x1 > 0 && (569 - y1) > 8 && y1 > 0) {
					//cout << "x1 test " << x1 << endl;
					//cout << "y1 = " << 569 - y1 << endl;
					xpm[569 - y1][x1] = 'x';
					//cout << "x1 " << x1 << endl;
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
							//cout << "i test" << i << endl;
							xpm[569 - tempLine->y1][i] = 'x';
							//cout << "i " << i << endl;
						}
					}
				}
				else {
					for (int i = tempLine->x2 + 1; i < tempLine->x1 + 1; i++) {
						if ((i - 1) >= 0 && (i - 1) <= 500) {
							//cout << "i test" << i << endl;
							xpm[569 - tempLine->y1][i] = 'x';
							//cout << "i " << i << endl;
						}
					}
				}
			}
			if (tempLine->x1 == tempLine->x2) {
				if (tempLine->y1 < tempLine->y2) {
					for (int i = 569 - tempLine->y2; i < 569 - tempLine->y1; i++) {
						if ((tempLine->x1) >= 0 && (tempLine->x1) <= 500) {
							//cout << "tempLine->x1 test " << tempLine->x1 << endl;
							xpm[i][tempLine->x1] = 'x';
							//cout << "tempLine->x1" << tempLine->x1 << endl;
						}
					}
				}
				else {
					for (int i = 569 - tempLine->y1; i < 569 - tempLine->y2; i++) {
						if ((tempLine->x1) >= 0 && (tempLine->x1) <= 500) {
							//cout << "tempLine->x1 test " << tempLine->x1 << endl;
						
							xpm[i][tempLine->x1] = 'x';
							//cout << "tempLine->x1 " << tempLine->x1 << endl;
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

vector<string> fillPolygon(Polygon* polygon, vector<string> xpm) {
	vector <Line*> scanLines;
	vector <Line*> fillLines;
	float za, zb;


	for (int i = 0; i < 501; i++) {
		Line* newLine = new Line(0, i, 0,  500, i, 0);
		scanLines.push_back(newLine);
	}

	for (int j = 0; j < 500; j++) {
	
		vector <Vertice*> intersectionPointList;
		vector <Line*> intersectedLines;
		for (int k = 0; k < polygon->polyLines.size(); k++) {
			//cout << k << endl;
			Vertice* scanLine1 = new Vertice(scanLines[j]->x1, scanLines[j]->y1, 0);
			Vertice* scanLine2 = new Vertice(scanLines[j]->x2, scanLines[j]->y2, 0);

			Vertice* polyLines1 = new Vertice(polygon->polyLines[k]->x1, polygon->polyLines[k]->y1, 0);
			Vertice* polyLines2 = new Vertice(polygon->polyLines[k]->x2, polygon->polyLines[k]->y2, 0);

			Vertice* intersectionPoint = intersectionOfPoints(scanLine1, scanLine2, polyLines1, polyLines2);
			intersectionPoint->yCoord = scanLine1->yCoord;

			if (intersectionPoint->xCoord >= 0 && intersectionPoint->yCoord >= 0) {
				if ((scanLine1->yCoord >= polyLines1->yCoord && scanLine1->yCoord <= polyLines2->yCoord) || (scanLine1->yCoord <= polyLines1->yCoord && scanLine1->yCoord >= polyLines2->yCoord)) {
					intersectedLines.push_back(polygon->polyLines[k]);

					int x = intersectionPoint->xCoord;
					int y = intersectionPoint->yCoord;
				  	za = polygon->polyLines[k]->z1 - (polygon->polyLines[k]->z1 - polygon->polyLines[k]->z2) * ((polygon->polyLines[k]->y1 - scanLine1->yCoord) / (polygon->polyLines[k]->y1 - polygon->polyLines[k]->y2));
					Vertice* vertice = new Vertice(float(x), float(y), za);
					polygon->pixels.push_back(vertice);
				
					intersectionPoint->zCoord = za;
					intersectionPointList.push_back(intersectionPoint);
				}
			}
		}
		sort(intersectionPointList.begin(), intersectionPointList.end(), sortVector);

		if (intersectionPointList.size() == 2) {
			for (int i = 0; i < intersectionPointList.size(); i += 2) {
				Line* newLine = new Line(intersectionPointList[i]->xCoord, intersectionPointList[i]->yCoord, 0, intersectionPointList[i + 1]->xCoord, intersectionPointList[i + 1]->yCoord, 0);

				if (newLine->x1 < newLine->x2) {
					for (int c = newLine->x1 + 1; c < newLine->x2 + 2; c++) {		
						if (c == 0) {
							c = 1;
						}
						if (xpm[569 - newLine->y1].size() == 504) {
							
							float newz = intersectionPointList[1]->zCoord - (intersectionPointList[1]->zCoord - intersectionPointList[0]->zCoord) * ((intersectionPointList[1]->xCoord - c) / (intersectionPointList[1]->xCoord - intersectionPointList[0]->xCoord));		
							Vertice* vertice = new Vertice(c, newLine->y1, newz);
							polygon->pixels.push_back(vertice);						
							
						}
					}
				}
				else {
					for (int d = newLine->x2 + 1; d < newLine->x1 + 2; d++) {			
						if (d == 0) {
							d = 1;
						}
						if (xpm[500 - newLine->y1].size() == 504) {
			
							float newz = intersectionPointList[1]->zCoord - (intersectionPointList[1]->zCoord - intersectionPointList[0]->zCoord) * ((intersectionPointList[1]->xCoord - d) / (intersectionPointList[1]->xCoord - intersectionPointList[0]->xCoord));
							Vertice* vertice = new Vertice(d, newLine->y1, newz);
							polygon->pixels.push_back(vertice);
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



Vertice* intersectionOfPoints(Vertice* p1, Vertice* p2, Vertice* p3, Vertice* p4)
{
	Vertice* intersectionPoint = new Vertice(1, 2, 0);


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

	float line1b = slope1*(l1p1x)-l1p1y;
	line1b = -line1b;

	float line2b = slope2*(l2p1x)-l2p1y;
	line2b = -line2b;

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

	return intersectionPoint;

}
void zbufferxpm(vector<Polygon*> newPolygons)
{
	for (int i = 0; i < 500; i++) {
		for (int k = 0; k < 500; k++) {
			//xpm[569 - k][i + 1] = '-';
			
		}
	}
	for (int j = 0; j < newPolygons.size(); j++) {
		//cout << j;
		for (int l = 0; l < newPolygons[j]->pixels.size(); l++) {
			if (j == 1) {
				
			}

			else{

				float pz = newPolygons[j]->pixels[l]->zCoord;
				float newfront = PRPZ - front / back - PRPZ;
				if (pz < newfront && pz > zbuffer2[int(newPolygons[j]->pixels[l]->xCoord)][int(newPolygons[j]->pixels[l]->yCoord)]) {
					zbuffer2[int(newPolygons[j]->pixels[l]->xCoord)][int(newPolygons[j]->pixels[l]->yCoord)] = pz;

					//cout << 569 - int(newPolygons[j]->pixels[l]->yCoord) << endl;
					if (pz > -1 && pz < -0.95) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord)+1] = 't'; 
					}
					else if (pz > -0.95 && pz < -0.9) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 's';
					}
					else if (pz > -0.9 && pz < -0.85) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'r';
					}
					else if (pz > -0.85 && pz < -0.80) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'q';
					}
					else if (pz > -0.80 && pz < -0.75) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'p';
					}
					else if (pz > -0.75 && pz < -0.70) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'o';
					}
					else if (pz > -0.70 && pz < -0.65) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'n';
					}
					else if (pz > -0.65 && pz < -0.60) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'm';
					}
					else if (pz > -0.60 && pz < -0.55) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'l';
					}
					else if (pz > -0.55 && pz < -0.50) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'k';
					}
					else if (pz > -0.50 && pz < -0.45) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'x';
					}
					else if (pz > -0.45 && pz < -0.40) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'a';
					}
					else if (pz > -0.40 && pz < -0.35) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'b';
					}
					else if (pz > -0.35 && pz < -0.30) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'c';
					}
					else if (pz > -0.30 && pz < -0.25) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'd';
					}
					else if (pz > -0.25 && pz < -0.20) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'e';
					}
					else if (pz > -0.20 && pz < -0.15) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'f';
					}
					else if (pz > -0.15 && pz < -0.10) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'g';
					}
					else if (pz > -0.10 && pz < -0.5) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'h';
					}
					else if (pz > -0.05 && pz < 0) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord+1) + 1] = 'i';
					}

				}
			}
		}
	}
}

void zbufferxpm2(vector<Polygon*> newPolygons)
{
	for (int i = 0; i < 500; i++) {
		for (int k = 0; k < 500; k++) {
			//xpm[569 - k][i + 1] = '-';

		}
	}
	for (int j = 0; j < newPolygons.size(); j++) {
		//cout << j;
		for (int l = 0; l < newPolygons[j]->pixels.size(); l++) {
			if (j == 1) {

			}

			else {

				float newfront;
				float pz = newPolygons[j]->pixels[l]->zCoord;

				if (parallelProjection == true) {
					newfront = 0;
				}
				else {
					newfront = PRPZ - front / back - PRPZ;
				}
				
				if (pz < newfront && pz > zbuffer2[int(newPolygons[j]->pixels[l]->xCoord)][int(newPolygons[j]->pixels[l]->yCoord)]) {
					zbuffer2[int(newPolygons[j]->pixels[l]->xCoord)][int(newPolygons[j]->pixels[l]->yCoord)] = pz;

					//cout << 569 - int(newPolygons[j]->pixels[l]->yCoord) << endl;
					if (pz > -1 && pz < -0.95) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'T';
					}
					else if (pz > -0.95 && pz < -0.9) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'S';
					}
					else if (pz > -0.9 && pz < -0.85) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'R';
					}
					else if (pz > -0.85 && pz < -0.80) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'Q';
					}
					else if (pz > -0.80 && pz < -0.75) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'P';
					}
					else if (pz > -0.75 && pz < -0.70) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'O';
					}
					else if (pz > -0.70 && pz < -0.65) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'N';
					}
					else if (pz > -0.65 && pz < -0.60) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'M';
					}
					else if (pz > -0.60 && pz < -0.55) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'L';
					}
					else if (pz > -0.55 && pz < -0.50) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'K';
					}
					else if (pz > -0.50 && pz < -0.45) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'J';
					}
					else if (pz > -0.45 && pz < -0.40) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'I';
					}
					else if (pz > -0.40 && pz < -0.35) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'H';
					}
					else if (pz > -0.35 && pz < -0.30) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'G';
					}
					else if (pz > -0.30 && pz < -0.25) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'F';
					}
					else if (pz > -0.25 && pz < -0.20) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'E';
					}
					else if (pz > -0.20 && pz < -0.15) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'D';
					}
					else if (pz > -0.15 && pz < -0.10) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'C';
					}
					else if (pz > -0.10 && pz < -0.5) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = 'B';
					}
					else if (pz > -0.05 && pz < 0) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord + 1) + 1] = 'A';
					}

				}
			}
		}
	}
}

void zbufferxpm3(vector<Polygon*> newPolygons)
{
	for (int i = 0; i < 500; i++) {
		for (int k = 0; k < 500; k++) {
			//xpm[569 - k][i + 1] = '-';

		}
	}
	for (int j = 0; j < newPolygons.size(); j++) {
		//cout << j;
		for (int l = 0; l < newPolygons[j]->pixels.size(); l++) {
			if (j == 1) {

			}

			else {

				float pz = newPolygons[j]->pixels[l]->zCoord;
				float newfront = PRPZ - front / back - PRPZ;
				if (pz < newfront && pz > zbuffer2[int(newPolygons[j]->pixels[l]->xCoord)][int(newPolygons[j]->pixels[l]->yCoord)]) {
					zbuffer2[int(newPolygons[j]->pixels[l]->xCoord)][int(newPolygons[j]->pixels[l]->yCoord)] = pz;

					//cout << 569 - int(newPolygons[j]->pixels[l]->yCoord) << endl;
					if (pz > -1 && pz < -0.95) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '+';
					}
					else if (pz > -0.95 && pz < -0.9) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '=';
					}
					else if (pz > -0.9 && pz < -0.85) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = ')';
					}
					else if (pz > -0.85 && pz < -0.80) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '(';
					}
					else if (pz > -0.80 && pz < -0.75) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '*';
					}
					else if (pz > -0.75 && pz < -0.70) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '&';
					}
					else if (pz > -0.70 && pz < -0.65) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '^';
					}
					else if (pz > -0.65 && pz < -0.60) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '%';
					}
					else if (pz > -0.60 && pz < -0.55) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '&';
					}
					else if (pz > -0.55 && pz < -0.50) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '#';
					}
					else if (pz > -0.50 && pz < -0.45) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '!';
					}
					else if (pz > -0.45 && pz < -0.40) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '0';
					}
					else if (pz > -0.40 && pz < -0.35) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '9';
					}
					else if (pz > -0.35 && pz < -0.30) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '8';
					}
					else if (pz > -0.30 && pz < -0.25) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '7';
					}
					else if (pz > -0.25 && pz < -0.20) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '6';
					}
					else if (pz > -0.20 && pz < -0.15) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '5';
					}
					else if (pz > -0.15 && pz < -0.10) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '4';
					}
					else if (pz > -0.10 && pz < -0.5) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '3';
					}
					else if (pz > -0.05 && pz < 0) {
						xpm[569 - int(newPolygons[j]->pixels[l]->yCoord)][int(newPolygons[j]->pixels[l]->xCoord) + 1] = '2';
					}

				}
			}
		}
	}
}
bool sortVector(Vertice* vertice1, Vertice* vertice2)
{
	return vertice1->xCoord < vertice2->xCoord;
}
