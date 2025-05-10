#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <optional>
#include <utility>
#include <optional>

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

	std::vector<Position> getVecteurPositionsAdjacentes() const;

	bool estAdjacente(const Position& position) const;

	bool operator==(const Position& position) const; 

	bool operator!=(const Position& position) const; 

	const Position operator+(const Position& position) const;

	const Position operator-(const Position& position) const;

	const Position getPositionAdjacente(Direction direction) const;

};

std::ostream& operator<<(std::ostream& flux, const Position& p); //afficher une Position

string directionToString(Direction dir);

std::ostream& operator<<(std::ostream& flux, const Direction& d); //afficher une Position


extern const std::vector<Position> direction_vecteur;

const Direction getDirectionOpposee(Direction dir);

//si cette fonction suivante ne marche pas, alors il faut vérifier que la version de l'IDE est au moins C++17
Direction coteTangent(const Position& a, const Position b);


class Tuile {
	std::array<Habitat, 2> paysages;
	std::array<Faune,3> faunes;
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
	std::array<pair<Tuile, JetonFaune>, 4> pioche;
	// Privation du constructeur
public:
	// Suppression du constructeur par copie et par affectation 
	Pioche(const Pioche&) = delete;
	Pioche& operator=(const Pioche&) = delete;


	// setterPair à indice specifique
	inline void setPair(size_t indice, const Tuile& tuile, const JetonFaune& jeton){
		if (indice < 4) {
			pioche[indice] = std::make_pair(tuile, jeton);
		}
		throw std::out_of_range("Indice hors intervalle de la taille de la pioche");
	}

	// getterPair à indice specifique
	inline pair<Tuile, JetonFaune> getPair(size_t indice) const {
		if (indice < 4) {
			return pioche[indice];
		}
		throw std::out_of_range("Indice hors intervalle de la taille de la pioche");
	}

	// verification si pioche contient au moins un type de JetonFaune de cardinalité == nombre fois
	// fauneCount les faunes indice dans l'ordre de Enum Class
	bool contientJetonIdentique(int nombre) const;

	int retourneIndiceFaune(Faune type) const;

	bool estTroisIdentique() const;

	bool estQuatreIdentique() const;

	void retirerPaire(size_t indice);

	Tuile& nouvelleTuile();
	JetonFaune& nouveauJetonFaune();
	
	void resetAllJetonFaune();
	void resetJetonFaune(const std::vector<int>& quiEnleverIndices);


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