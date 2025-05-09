///Veuillez vous assurer que la version de votre IDE est au moins C++17 avant de compiler.
#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <algorithm>
#include <optional>
#include <unordered_map>
#include <fstream>
#include <json\json.h>
using namespace std;

enum class Habitat { marais, fleuve, montagne, prairie, foret };
enum class Faune { saumon, ours, buse, renard, wapiti, rien };
enum class Direction { NordEst = 0, Est = 1, SudEst = 2, SudOuest = 3, Ouest = 4, NordOuest = 5, Inconnue = -1};

string habitatToString(Habitat habitat);
string fauneToString(Faune faune);
Faune stringToFaune(const string& s);
string directionToString(Direction dir);

ostream& operator<<(ostream& flux, Habitat h);
ostream& operator<<(ostream& flux, Faune f);
ostream& operator<<(ostream& flux, Direction d);

class Position {

	int q, r, s;

public:

	Position(int x1 = 0, int x2 = 0, int x3 = 0) : q(x1), r(x2), s(x3) {
		if (q + r + s != 0) {
			throw std::invalid_argument("La somme des coordonnees doivent donner 0. Veuillez les reviser.");
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

ostream& operator<<(ostream& flux, const Position& p);

string directionToString(Direction dir);

extern const vector <Position> direction_vecteur;

Direction getDirectionOpposee(Direction dir);

Direction coteTangent(const Position& a, const Position& b);

void testClassePosition();


class Tuile {
	array<Habitat, 6> habitats;
	vector<Faune> faunes; //un vector est adapté étant donné que le nombre de faunes varient entre 1 et 3
	bool donneJetonNature;
	optional<Faune> faunePlace;
	unique_ptr<Position> position; //composition
	bool placementConfirme;

public:

	//constructeur principal
	Tuile(	const array<Habitat,6>& habitats, 
			const vector<Faune>& faunes, 
			bool nature = false, 
			bool jetonPresent = false,
			Position* p = nullptr,
			bool place = false) 
			: habitats(habitats), faunes(faunes), 
			  donneJetonNature(nature), faunePlace(nullopt),
			  position(p), placementConfirme(place) {
		if (faunes.size() < 1 && faunes.size() > 3)
			throw std::invalid_argument("Une tuile doit avoir entre 1 et 3 faunes.");
	}

	///TODO ? un constructeur specifique pour extraire JSON?

	const array<Habitat, 6>& getHabitats() const { return habitats; }
	const vector<Faune>& getFaunes() const { return faunes; }
	bool getDonneJetonNature() const { return donneJetonNature; }
	bool JetonFaunePresent() const { return faunePlace.has_value(); }
	Faune getFaunePlace() const { return faunePlace.value_or(Faune::rien); }
	const Position& getPosition() const { return *(position.get()); }
	bool getPlacementConfirme() const { return placementConfirme; }


	void setPosition(int q, int r, int s) {
		if (! placementConfirme)
			position = make_unique<Position>(q, r, s);
	}

	void placerJetonFaune(Faune faune);

	void confirmerPlacement() { placementConfirme = true; }

	void pivoterHoraire();

	void pivoterAntiHoraire();

};

ostream& operator<<(ostream& flux, const Tuile& tuile);

void testClasseTuile();

class JetonFaune {
	Faune type;
public:
	JetonFaune(Faune type) : type(type) {}
	Faune getType() const { return type; };
};

ostream& operator<<(ostream& os, const JetonFaune& j);


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

class GestionInstanciation {
public:
	void instancierTuiles(const string& fileName, vector<Tuile>& tuiles);

	bool stringToBool(const string& str) {
		return str == "true";
	}

	Habitat stringToHabitat(const string& s) {
		if (s == "marais") return Habitat::marais;
		if (s == "fleuve") return Habitat::fleuve;
		if (s == "montagne") return Habitat::montagne;
		if (s == "prairie") return Habitat::prairie;
		if (s == "forêt") return Habitat::foret;
		throw invalid_argument("Habitat inconnu: " + s);
	}

	Faune stringToFaune(const string& s) {
		if (s == "saumon") return Faune::saumon;
		if (s == "ours") return Faune::ours;
		if (s == "buse") return Faune::buse;
		if (s == "renard") return Faune::renard;
		if (s == "wapiti") return Faune::wapiti;
		return Faune::rien; // default case
	}
};