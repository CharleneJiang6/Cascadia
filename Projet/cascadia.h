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

	vector<Position> getPositionsAdjacentes() const {
		return {
			Position(q + 1, r, s - 1),    // Nord-Est, côté 0
			Position(q + 1, r - 1, s),    // Est, côté 1
			Position(q, r - 1, s + 1),    // Sud-Est, côté 2
			Position(q - 1, r, s + 1),    // Sud-Ouest, côté 3
			Position(q - 1, r + 1, s),    // Ouest, côté 4
			Position(q, r + 1, s - 1),    // Nord-Ouest, côté 5 			
		};
	}

	bool estAdjacente(const Position& position) const {
		const int dq = abs(q - position.q);
		const int dr = abs(r - position.r);
		const int ds = abs(s - position.s);
		return (dq + dr + ds) == 2;
	}
	
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