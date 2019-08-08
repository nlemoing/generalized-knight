#include "params.h"
#include <iostream>

using namespace std;

void imageParams(int &lo, int &hi, int &sat, int &val, bool &saveIntermediate) {
	cout << "Image params: low hue, high hue, saturation, brightness" << endl;
	cin >> lo >> hi >> sat >> val;
	cout << "Save intermediate images? [y/n]" << endl;
	char c;
	cin >> c;
	saveIntermediate = (c == 'y' || c == 'Y');
}

void boardParams(int &width, int &height, int &knightA, int &knightB) {
	cout << "Board params: width, height" << endl;
	cin >> width >> height;
	cout << "Knight params: a, b" << endl;
	cin >> knightA >> knightB;
}
