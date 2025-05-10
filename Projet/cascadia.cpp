#include <iostream>
#include "cascadia.h"


std::ostream& operator<<(std::ostream& flux, const Position& p)
{
	flux << "(" << p.getQ() << "," << p.getR() << "," << p.getS() << ")";
	return flux;
}

std::string directionToString(Direction dir) {
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

std::ostream& operator<<(std::ostream& flux, const Direction& d)
{
	flux << directionToString(d);
	return flux;
}

const Direction getDirectionOpposee(Direction dir) {
	return static_cast<Direction>((static_cast<int>(dir) + 3) % 6);
}

//par exemple, sur le coté NordOuest de a se trouve b, alors la fonction retourne NordOuest
Direction coteTangent(const Position& a, const Position& b)
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

std::vector<Position> Position::getVecteurPositionsAdjacentes() const {
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
bool Pioche::contientJetonIdentique(int nombre) const {
	std::array<int, 5> fauneCount{0};
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
	return contientJetonIdentique(3);
}

bool Pioche::estQuatreIdentique() const {
	return contientJetonIdentique(4);
}

void Pioche::retirerPaire(size_t indice) {
	if (indice < 4) {
		pioche[indice] = std::make_pair(nouvelleTuile(),nouveauJetonFaune());
	}
	else {
		throw std::out_of_range("Indice hors intervalle de la taille de la pioche");
	}
}

void Pioche::resetAllJetonFaune(){
	for (int i = 0; i < 4; i++) {
		pioche[i].second = nouveauJetonFaune();
		// sans faire faune type -- (t'as dis quoi nicolas?)
	}
}

void Pioche::resetJetonFaune(const std::vector<int>& quiEnleverIndices) {
	for (int i : quiEnleverIndices) {
		if (i >= 0 && i < 4) {
			pioche[i].second = nouveauJetonFaune();
		} else {
			//throw std::out_of_range("Indice hors intervalle de la taille de la pioche, ignoré");
			//^si on veut que le programme s'arrête là, sinon:
			std::cerr << "Indice " << i << " hors intervalle. Ignoré.\n";
		}
	}
}

void Pioche::removePair(size_t indiceTuile, size_t indiceJetonFaune) {
	for (size_t i = indiceJetonFaune; i < 1; i--) { //on remets des index 1 à celui du jeton pris à leur place où ils 'tombent'
		pioche[i].second = pioche[i - 1].second;//!!!!!!!!!!!!!!!!!!!!est ce qu'on aurait besoin d'un constructeur par recopie de tuile et jeton?
	}
	for (size_t i = indiceTuile; i < 1; i--) { //same for tuile
		pioche[i].first = pioche[i - 1].first;
	}
	pioche[0]= std::make_pair(nouvelleTuile(), nouveauJetonFaune());//on génère le nouveau jeton et tuile en tete de la pioche
}
//^when you choose une pair (tuile et jetonFaune) en utilisant un jetonNature: they fall down and you get new pairs






//to be continued:
void Pioche::removeLastPair() { //!!!!!!!!!!!!!!!!!!!!!!!!!à en parler. simulates fake player //i think this function should be done after choosing the architecture of how the game works
	//if (pioche[3]) {//si la dernière est valide == le joueur n'a pas choisi cette paire
	//	//enlever la dernière paire (indice 3)
	//	pioche[3] = pioche[2];
	//	pioche[2] = pioche[1];
	//	pioche[1] = pioche[0];
	//	pioche[0] = std::make_pair(nouvelleTuile(), nouveauJetonFaune());
	//}
	//else {
	//	//enlever la paire à l'indice 2 (dernière paire valide)

	//}
}