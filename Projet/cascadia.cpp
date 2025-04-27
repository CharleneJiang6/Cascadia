#include <iostream>
#include "cascadia.h"
using namespace std;

ostream& operator<<(ostream& flux, const Position& p)
{
	flux << "(" << p.getQ() << "," << p.getR() << "," << p.getS() << ")";
	return flux;
}

//A REVOIR LES COORDONNNEES (chosir orientation des axes)
vector<Position> Position::getPositionsAdjacentes() const {
	return {
		Position(q + 1, r, s - 1),    // Nord-Est, côté 0
		Position(q + 1, r - 1, s),    // Est, côté 1
		Position(q, r - 1, s + 1),    // Sud-Est, côté 2
		Position(q - 1, r, s + 1),    // Sud-Ouest, côté 3
		Position(q - 1, r + 1, s),    // Ouest, côté 4
		Position(q, r + 1, s - 1),    // Nord-Ouest, côté 5 			
	};
}

bool Position::estAdjacente(const Position& position) const {
	const int dq = abs(q - position.q);
	const int dr = abs(r - position.r);
	const int ds = abs(s - position.s);
	return (dq + dr + ds) == 2;
}

bool Position::operator==(const Position& position) const {
	return q == position.q && r == position.r && s == position.s;
}

bool Position::operator!=(const Position& position) const {
	return !(*this == position);
}

const Position& Position::operator+(const Position& position) const { 
	return Position(q + position.getQ(), r + position.getR(), s + position.getS());
}

const Position& Position::operator-(const Position& position) const {
	return Position(q - position.getQ(), r - position.getR(), s - position.getS());
}