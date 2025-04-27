#include <iostream>
using namespace std;
#include "cascadia.h"

#include <unordered_map>

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

	//cout << (p + q);

	//vector <Position> direction_vecteur = {
	//{+1, -1, 0},
	//{+1, 0, -1},
	//{0, +1, -1},
	//{-1, +1, 0},
	//{-1, 0, +1},
	//{0, -1, +1}
	//};


	//Position est = direction_vecteur[static_cast<int>(Direction::Est)];  
	//int inco = static_cast<int>(Direction::Inconnue);

	//cout << inco << "\n\n";// (+1, -1, 0)

	//cout << (q = direction_vecteur[static_cast<int>(Direction::SudOuest)]);

	//cout << p.getPositionAdjacente(Direction::SudOuest);

	//cout << (direction_vecteur[static_cast<int>(getDirectionOpposee(Direction::NordEst))]);

	//cout << directionToString(Direction::NordEst);

	cout << (direction_vecteur[static_cast<int>(coteTangent(p,q))]);

}