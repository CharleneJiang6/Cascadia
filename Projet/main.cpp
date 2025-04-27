#include <iostream>
using namespace std;
#include "cascadia.h"

int main() {
	cout << "hello world" << endl;

	//test Position
	Position p(1, 0, -1);
	cout << p;

	Position q(0, 0, 0);
	cout << q << endl;

	//cout << p.estAdjacente(q) << endl;

	//cout << (p == q) << endl;
	//cout << (p != q) << endl;
	//
	//cout << p.getPositionsAdjacentes().at(0);

	cout << (p + q);
}