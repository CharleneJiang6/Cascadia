#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <optional>

using namespace std;

enum class Habitat { marais, fleuve, montagne, prairie, foret };
enum class Faune { saumon, ours, buse, renard, wapiti };

enum class Direction { NordEst = 0, Est = 1, SudEst = 2, SudOuest = 3, Ouest = 4, NordOuest = 5, Inconnue = -1};

class Position {

	int q, r, s;

public:

	Position(int x1 = 0, int x2 = 0, int x3 = 0) : q(x1), r(x2), s(x3) {
		if (q + r + s != 0) {
			throw "La somme des coordonnees doivent donner 0. Veuillez les reviser.";
		}
	}

	int getQ() const { return q; }
	int getR() const { return r; }
	int getS() const { return s; }

	vector<Position> getVecteurPositionsAdjacentes() const;

	bool estAdjacente(const Position& position) const;

	bool operator==(const Position& position) const; 

	bool operator!=(const Position& position) const; 

	const Position operator+(const Position& position) const;

	const Position operator-(const Position& position) const;

	const Position getPositionAdjacente(Direction direction) const;

};

ostream& operator<<(ostream& flux, const Position& p); //afficher une Position

string directionToString(Direction dir);

ostream& operator<<(ostream& flux, const Direction& d); //afficher une Position


extern const vector <Position> direction_vecteur;

const Direction getDirectionOpposee(Direction dir);

//si cette fonction suivante ne marche pas, alors il faut vérifier que la version de l'IDE est au moins C++17
Direction coteTangent(const Position& a, const Position b);

void testClassePosition();


class Tuile {
	array<Habitat, 6> habitats;
	vector<Faune> faunes; //un vector est adapté étant donné que le nombre de faunes varient entre 1 et 3
	bool donneJetonNature;
	bool jetonPlace;
	Position* position; //composition


public:

	//constructeur principal
	Tuile(	const array<Habitat,6>& habitats, 
			const vector<Faune>& faunes, 
			bool nature = false, 
			bool jetonPresent = false,
			Position* p = nullptr) 
			: habitats(habitats), faunes(faunes), 
			  donneJetonNature(nature), jetonPlace(jetonPresent), position(p) {
		if (faunes.size() < 1 && faunes.size() > 3)
			throw "Une tuile doit avoir entre 1 et 3 faunes.";
	}

	///TODO ? un constructeur specifique pour extraire JSON?

	///getters
	const array<Habitat, 6>& getHabitats() const { return habitats; }
	const vector<Faune>& getFaunes() const { return faunes; }
	bool getDonneJetonNature() const { return faunes.size() == 1; }
	bool getJetonPlace() const { return jetonPlace; }
	const Position& getPosition() const { return *position; }

	///TODO : definir les methodes
	void confirmerPlacement();
	void pivoterSensHoraire();
	void pivoterSensAntiHoraire();

};

///TODO : cout << Tuile ?

class JetonFaune {
	Faune type;
public:
	//getters + constructeur
};

class CarteMarquage {
	Faune faune;

public :
	//getters + constructeur
};

class Pioche {
	//todo
};

class EnvJoueur {
	string pseudo;
	//unordered_map<Position, Tuile, PositionHash> ?
	size_t nbJetonNature;
	size_t scoreFinal;

public:
	//getters
	//setters
	//methods
};

class Partie {
	size_t nbJoeurs;
	size_t compteurTours;
	stack<Tuile> tuilesRestantes;
	stack<JetonFaune> jetonsRestants;
	EnvJoueur* currentJoeur;


public:
	//getters
	//setters
	//methods
};