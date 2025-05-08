#include <iostream>
#include "cascadia.h"


ostream& operator<<(ostream& flux, const Position& p)
{
	flux << "(" << p.getQ() << "," << p.getR() << "," << p.getS() << ")";
	return flux;
}

string directionToString(Direction dir) {
	switch (dir) {
	case Direction::Est:       return "Est";
	case Direction::NordEst:   return "NordEst";
	case Direction::NordOuest: return "NordOuest";
	case Direction::Ouest:     return "Ouest";
	case Direction::SudOuest:  return "SudOuest";
	case Direction::SudEst:    return "SudEst";
	default:                   return "Inconnu";
	}
}

ostream& operator<<(ostream& flux, const Direction& d)
{
	flux << directionToString(d);
	return flux;
}

const Direction getDirectionOpposee(Direction dir) {
	return static_cast<Direction>((static_cast<int>(dir) + 3) % 6);
}

//par exemple, sur le coté NordOuest de a se trouve b, alors la fonction retourne NordOuest
Direction coteTangent(const Position& a, const Position b)
{
	if (a.estAdjacente(b)) {
		for (int i = 0; i < 6; ++i) {
			Direction dir = static_cast<Direction>(i);
			Position candidate = a.getPositionAdjacente(dir);
			if (candidate == b) return dir;
		}
	}

	return Direction::Inconnue; 
}

vector<Position> Position::getVecteurPositionsAdjacentes() const {
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

const Position Position::operator+(const Position& position) const { 
	return Position(q + position.getQ(), r + position.getR(), s + position.getS());
}

const Position Position::operator-(const Position& position) const {
	return Position(q - position.getQ(), r - position.getR(), s - position.getS());
}

const Position Position::getPositionAdjacente(Direction direction) const
{
	const Position& pos = direction_vecteur[static_cast<int>(direction)];
	return Position(q + pos.getQ(), r + pos.getR(), s + pos.getS());
}

const std::vector<Position> direction_vecteur = {
	Position(1, -1, 0), //NordEst, 0
	Position(1, 0, -1), //Est, 1
	Position(0, 1, -1), //SudEst, 2
	Position(-1, 1, 0), //SudOuest, 3
	Position(-1, 0, 1), //Ouest,4
	Position(0, -1, 1)  //NordOuest,5
};

// les methodes de la classe Pioche
// verification si pioche contient au moins un type de JetonFaune de cardinalité == count fois
	// fauneCount les faunes indice dans l'ordre de Enum Class
bool Pioche::aIdentiqueJeton(int nombre) const {
	array<int, 5> fauneCount;
	// compter respectivement le nb de chaque faune presente
	for (const auto& pair : pioche) {
		fauneCount[retourneIndiceFaune(pair.second.getType())]++;
	}
	// verification du nombre
	for (const auto& value : fauneCount) {
		if (value == nombre) {
			return true;
		}
	}
	return false;
}

int Pioche::retourneIndiceFaune(Faune type) const {
	switch (type) {
	case Faune::saumon: return 0;
	case Faune::ours:   return 1;
	case Faune::buse:   return 2;
	case Faune::renard: return 3;
	case Faune::wapiti: return 4;
	default: throw std::invalid_argument("Type de Faune Inconnu");
	}
}

bool Pioche::estTroisIdentique() const {
	return aIdentiqueJeton(3);
}

bool Pioche::estQuatreIdentique() const {
	return aIdentiqueJeton(4);
}

void Pioche::retirerPaire(size_t indice) {
	if (indice < 4) {
		pioche[indice] = make_pair(nouvelleTuile(),nouveauJetonFaune());
	}
	throw out_of_range("Indice hors intervalle de la taille de la pioche");
}

void Pioche::resetJetonFaune(){
	for (int i = 0; i < 4; i++) {
		pair<Tuile, JetonFaune> pair = getPair(i);
		pair = make_pair(pair.first, nouveauJetonFaune());
		// sans faire faune type --
	}
}