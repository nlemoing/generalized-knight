#include "params.h"
#include <iostream>

using namespace std;

void imageParams(int &hlo, int &slo, int &vlo, int &hhi, int &shi, int &vhi, bool &saveIntermediate) {
	cerr << "Low color: hue, saturation, brightness" << endl;
	cin >> hlo >> slo >> vlo;
	cerr << "High color: hue, saturation, brightness" << endl;
	cin >> hhi >> shi >> vhi;
	cerr << "Save intermediate images? [y/n]" << endl;
	char c;
	cin >> c;
	saveIntermediate = (c == 'y' || c == 'Y');
}

void boardParams(int &width, int &height, int &scale, int &knightA, int &knightB) {
	cerr << "Board params: width, height, scale factor" << endl;
	cin >> width >> height >> scale;
	cerr << "Knight params: a, b" << endl;
	cin >> knightA >> knightB;
}
