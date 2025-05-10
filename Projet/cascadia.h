///Veuillez vous assurer que la version de votre IDE est au moins C++17 avant de compiler.
///Veuillez vous assurer avoir telecharger le dossier "include", afin de permettre le chargement du fichier "json.h".
#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <algorithm>
#include <optional>
#include <unordered_map>
#include <fstream>
#include "include\json\json.h"
#include <random>
using namespace std;

enum class Habitat { marais, fleuve, montagne, prairie, foret };
enum class Faune { saumon, ours, buse, renard, wapiti, rien };
enum class Direction { NordEst = 0, Est = 1, SudEst = 2, SudOuest = 3, Ouest = 4, NordOuest = 5, Inconnue = -1};

string habitatToString(Habitat habitat);
string fauneToString(Faune faune);
string directionToString(Direction dir);
Faune stringToFaune(const string& s);
Habitat stringToHabitat(const string& s);
bool stringToBool(const string& str);

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

//groupement de fonctions utiles pour la manipulation des fichiers JSON
namespace GestionTuiles {
	void instancierTuiles(const std::string& fichier, std::vector<Tuile>& ensembleTuiles);
	void instancierTuilesDepart(const std::string& fichier, std::vector<std::vector<Tuile>>& ensembleTripletsDepart);
	void melangerTuiles(std::vector<Tuile>& tuiles);
	Tuile depilerTuile(std::vector<Tuile>& tuiles);
}

void testGestionTuiles();