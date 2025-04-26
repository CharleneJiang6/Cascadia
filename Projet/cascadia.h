#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum class Habitat { marais, fleuve, montagne, prairie, foret };
enum class Faune { saumon, ours, buse, renard, wapiti };

class Position {
	int q, r, s;

public:
	//definir setter??

	int getQ() const { return q; }
	int getR() const { return r; }
	int getS() const { return s; }

	Position(int x1 = 0, int x2 = 0, int x3 = 0) : q(x1), r(x2), s(x3) {
		if (q + r + s != 0) {
			throw "La somme des coordonnees doivent donner 0. Veuillez les reviser.";
		}
	}

	//definir mehtodes
};

ostream& operator<<(ostream& flux, const Position& p); //afficher une Position

class Tuile {
	Habitat paysages[2]; //faut-il un indice pour surveiller le nb réel de Habitat?
	Faune faunes[3];
	size_t nbPaysages;
	size_t nbFaunes;
	bool jetonPlace;

public:
	//definir getter, setter, constructeur, methodes

	bool donneJetonNature() const { return nbFaunes == 0; }

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
	vector<Tuile> tuilesRestantes;
	vector<JetonFaune> jetonsRestants;
	EnvJoueur* currentJoeur;


public:
	//getters
	//setters
	//methods
};