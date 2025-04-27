#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <array>

using namespace std;

enum class Habitat { marais, fleuve, montagne, prairie, foret };
enum class Faune { saumon, ours, buse, renard, wapiti };

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

	vector<Position> getPositionsAdjacentes() const;

	bool estAdjacente(const Position& position) const;

	bool operator==(const Position& position) const; 

	bool operator!=(const Position& position) const; 

	const Position& operator+(const Position& position) const;

	const Position& operator-(const Position& position) const;

};

ostream& operator<<(ostream& flux, const Position& p); //afficher une Position

class Tuile {
	array<Habitat, 2> paysages;
	array<Faune,3> faunes;
	bool jetonPlace;

public:
	//definir getter, setter, constructeur, methodes

	bool donneJetonNature() const { return faunes.size() == 1; }

};

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