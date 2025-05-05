#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <optional>
#include <utility>
#include <unordered_map>

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
	
	// constructeur a modifier
	Tuile() : jetonPlace(false) {}
	bool donneJetonNature() const { return faunes.size() == 1; }

};

class JetonFaune {
	Faune type;
public:
	//getters + constructeur

	// constructeur
	JetonFaune(Faune type) : type(type) {}

	// getter pour type
	Faune getType() const { return type; }
};

class CarteMarquage {
	Faune faune;

public :
	//getters + constructeur
};

class Pioche {
private:
	array<pair<Tuile, JetonFaune>, 4> pioche;
	// Privation du constructeur
	Pioche() = default;
public:
	// Suppression du constructeur par copie et par affectation 
	Pioche(const Pioche&) = delete;
	Pioche& operator=(const Pioche&) = delete;

	// Singleton
	inline static Pioche& getInstance() {
		static Pioche instance; // Guaranteed to be destroyed and instantiated on first use
		return instance;
	}

	// setterPair à indice specifique
	inline void setPair(size_t index, const Tuile& tuile, const JetonFaune& jeton){
		if (index < pioche.size()) {
			pioche[index] = make_pair(tuile, jeton);
		}
		throw out_of_range("Indice hors intervalle de la taille de la pioche");
	}

	// getterPair à indice specifique
	inline pair<Tuile, JetonFaune> getPair(size_t index) const {
		if (index < pioche.size()) {
			return pioche[index];
		}
		throw out_of_range("Indice hors intervalle de la taille de la pioche");
	}

	// verification si pioche contient au moins un type de JetonFaune de cardinalité == count fois
	// fauneCount les faunes indice dans l'ordre de Enum Class
	bool hasIdenticalJetonFaune(int count) const;

	int getCorrespondingIndexFaune(Faune type) const;

	bool hasThreeIdentical() const;

	bool hasFourIdentical() const;
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