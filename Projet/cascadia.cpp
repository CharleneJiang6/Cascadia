#include <iostream>
#include "cascadia.h"

//POSITION

std::ostream& operator<<(std::ostream& flux, const Position& p)
{
	flux << "(" << p.getQ() << "," << p.getR() << "," << p.getS() << ")";
	return flux;
}

std::string habitatToString(Habitat habitat) {
	switch (habitat) {
	case Habitat::marais:       return "marais";
	case Habitat::fleuve:		return "fleuve";
	case Habitat::montagne:		return "montagne";
	case Habitat::prairie:		return "prairie";
	case Habitat::foret:		return "foret";
	default:                    return "rien";
	}
}

std::string fauneToString(Faune faune) {
	switch (faune) {
	case Faune::saumon:			return "saumon";
	case Faune::ours:			return "ours";
	case Faune::buse:			return "buse";
	case Faune::renard:			return "renard";
	case Faune::wapiti:			return "wapiti";
	case Faune::rien:			return "rien";
	default:                    return "rien";
	}
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

std::ostream& operator<<(std::ostream& flux, Habitat h) {
	flux << habitatToString(h);
	return flux;
}

std::ostream& operator<<(std::ostream& flux, Faune f) {
	flux << fauneToString(f);
	return flux;
}

std::ostream& operator<<(std::ostream& flux, Direction d) {

	flux << directionToString(d);
	return flux;
}

Direction getDirectionOpposee(Direction dir) {
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

Faune stringToFaune(const string& s) {
	if (s == "saumon")      return Faune::saumon;
	else if (s == "ours")   return Faune::ours;
	else if (s == "buse")   return Faune::buse;
	else if (s == "renard") return Faune::renard;
	else if (s == "wapiti") return Faune::wapiti;
	else if (s == "rien")	return Faune::rien;
	else throw std::invalid_argument("Faune inconnu : " + s);
}

void testClassePosition(){
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

	cout << (direction_vecteur[static_cast<int>(coteTangent(p, q))]);
}

std::ostream& operator<<(std::ostream& flux, const Tuile& tuile) {
	const auto& habitats = tuile.getHabitats();
	const auto& faunes = tuile.getFaunes();

	flux << "TUILE : \n";

	flux << "\t- Habitats : ";
	for (Habitat h : habitats) {
		flux << habitatToString(h) << ", ";
	}
	flux << "\n";

	flux << "\t- Faunes : ";
	for (Faune f : faunes) {
		flux << fauneToString(f) << ", ";
	}
	flux << "\n";

	if (tuile.getPlacementConfirme())
		flux << "\t- Position : " << tuile.getPosition() << "\n";

	if (tuile.getDonneJetonNature())
		flux << "\t- Donne Jeton Nature.\n";

	if (tuile.JetonFaunePresent())
		flux << "\t- Faune placée : " << fauneToString(tuile.getFaunePlace()) << ".\n";

	return flux;
}

void Tuile::placerJetonFaune(Faune faune) {
	if (!JetonFaunePresent() && find(faunes.begin(), faunes.end(), faune) != faunes.end())
		faunePlace = faune;
	else
		throw "!La faune ne peut pas être placée ici!\n";
}

void Tuile::pivoterHoraire() {
	rotate(habitats.rbegin(), habitats.rbegin() + 1, habitats.rend());
}

void Tuile::pivoterAntiHoraire() {
	rotate(habitats.begin(), habitats.begin() + 1, habitats.end());
}


void testClasseTuile() {
	std::array<Habitat, 6> hab = {Habitat::fleuve, Habitat::fleuve, Habitat::fleuve,
							Habitat::foret, Habitat::foret, Habitat::foret} ;
	std::vector<Faune> fau = { Faune::buse,Faune::renard,Faune::ours };
	
	Tuile t = Tuile(hab, fau);

	try {
		t.placerJetonFaune(Faune::buse);
	} catch (const char* e) {
		cout << e;
	}

	t.setPosition(0, 1, -1);
	t.confirmerPlacement();
	t.pivoterHoraire();
	t.pivoterAntiHoraire();

	cout << t;
}