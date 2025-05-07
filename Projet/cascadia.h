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
	
	JetonFaune(Faune type) : type(type) {}
	Faune getFaune() const { return type; };

	void setType(const string& t); 
	///TODO setType: definir la fonction en faisant des verifs avant si le type est connu parmi les Faunes définies

};

///TODO: cout << JetonFaune


/// Classe abstraite avec méthode virtuelle pure
class CarteMarquage {
	Faune faune;

public :
	virtual int methodeCalcul() const = 0;
	///TODO : getter
	///TODO : constructeur
};

class CarteSaumon : public CarteMarquage {

};

class CarteOurs : public CarteMarquage {

};

class CarteBuse : public CarteMarquage {

};

class CarteRenard : public CarteMarquage {

};

class CarteWapiti : public CarteMarquage {
	
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