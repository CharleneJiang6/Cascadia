#include <iostream>
#include "cascadia.h"
using namespace std;

ostream& operator<<(ostream& flux, const Position& p)
{
	flux << "(" << p.getQ() << "," << p.getR() << "," << p.getS() << ")";
	return flux;
}

string habitatToString(Habitat habitat) {
	switch (habitat) {
	case Habitat::marais:       return "marais";
	case Habitat::fleuve:		return "fleuve";
	case Habitat::montagne:		return "montagne";
	case Habitat::prairie:		return "prairie";
	case Habitat::foret:		return "foret";
	default:                    return "rien";
	}
}

string fauneToString(Faune faune) {
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

Faune stringToFaune(const string& s) {
	if (s == "saumon") return Faune::saumon;
	if (s == "ours")   return Faune::ours;
	if (s == "buse")   return Faune::buse;
	if (s == "renard") return Faune::renard;
	if (s == "wapiti") return Faune::wapiti;
	if (s == "rien")	return Faune::rien;
	throw std::invalid_argument("Faune inconnu : " + s);
}

Habitat stringToHabitat(const string& s) {
	if (s == "marais")		return Habitat::marais;
	if (s == "fleuve")		return Habitat::fleuve;
	if (s == "montagne")	return Habitat::montagne;
	if (s == "prairie")		return Habitat::prairie;
	if (s == "forêt")		return Habitat::foret;
	throw std::invalid_argument("Habitat inconnu: " + s);
}

string directionToString(Direction dir) {
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

bool stringToBool(const string& str) {
	return str == "true";
}

ostream& operator<<(ostream& flux, Habitat h) {
	flux << habitatToString(h);
	return flux;
}

ostream& operator<<(ostream& flux, Faune f) {
	flux << fauneToString(f);
	return flux;
}

ostream& operator<<(ostream& flux, Direction d) {

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


vector<Position> Position::getVecteurPositionsAdjacentes() const {
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

ostream& operator<<(ostream& flux, const Tuile& tuile) {
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
		throw std::invalid_argument("!La faune ne peut pas être placée ici!\n");
}

void Tuile::pivoterHoraire() {
	rotate(habitats.rbegin(), habitats.rbegin() + 1, habitats.rend());
}

void Tuile::pivoterAntiHoraire() {
	rotate(habitats.begin(), habitats.begin() + 1, habitats.end());
}


void testClasseTuile() {
	array<Habitat, 6> hab = {Habitat::fleuve, Habitat::fleuve, Habitat::fleuve, 
							Habitat::foret, Habitat::foret, Habitat::foret} ;
	vector<Faune> fau = { Faune::buse,Faune::renard,Faune::ours };
	
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

ostream& operator<<(ostream& os, const JetonFaune& j) {
	os << fauneToString(j.getType());
	return os;
}


vector<Tuile> GestionTuiles::instancierTuiles(const string& fichier) {
	std::ifstream f(fichier);
	if (!f) throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + fichier);

	vector <Tuile> tuiles;

	json data = json::parse(f);

	for (const auto& tuile : data["tuiles"]) {

		// Conversion des habitats
		array<Habitat, 6> habitats;
		size_t i = 0;
		for (auto habitat : tuile["habitats"]) {
			habitats[i] = stringToHabitat(habitat.get<std::string>()); 
			i++;
		}

		if (i != 6 || i > habitats.size())
			throw std::runtime_error("Une tuile doit possède exactement 6 habitats !");

		// Conversion des faunes
		vector<Faune> faunes;
		for (auto faune : tuile["faunes"]) {
			faunes.push_back(stringToFaune(faune.get<std::string>()));
		}

		if (faunes.size() < 1 || faunes.size() > Tuile::maxFaunes)
		throw std::runtime_error("Le nombre de faunes qu'une tuile habrite va 1 a " + std::to_string(Tuile::maxFaunes));

		bool donneJetonNature = tuile.value("donneJetonNature", false); //false, valeur par défaut
		
		// Construction d'une Tuile directement dans le conteneur tuiles
		tuiles.emplace_back(habitats, faunes, donneJetonNature);
	}

	return tuiles;
}


///TODO : revoir ça pour être conforme à nlohmann::json

//void GestionTuiles::instancierTuilesDepart(const string& fichier, vector<vector<Tuile>>& ensembleTuilesDepart) {
//	ifstream file(fichier);
//	if (!file.is_open()) {
//		throw runtime_error("Impossible d'ouvrir le fichier JSON.");
//	}
//
//	Json::Value root;
//	file >> root;
//
//	// Check if the root has the expected structure
//	if (!root.isMember("tuiles_depart") || !root["tuiles_depart"].isArray()) {
//		throw runtime_error("Format JSON incorrect : 'tuiles_depart' manquant ou non un tableau.");
//	}
//
//	size_t j = 0;
//	for (const auto& triplet : root["tuiles_depart"]) {
//		if (!triplet.isMember("triplet") || !triplet["triplet"].isArray()) {
//			throw runtime_error("Format JSON incorrect : 'triplet' manquant ou non un tableau.");
//		}
//
//		for (const auto& tuile : triplet["triplet"]) {
//			if (!tuile.isMember("tuile") || !tuile["tuile"].isObject()) {
//				throw runtime_error("Format JSON incorrect : 'tuile' manquant ou non un objet.");
//			}
//
//			const auto& donnee = tuile["tuile"];
//
//			array<Habitat, 6> habitats;
//			size_t i = 0;
//			if (donnee.isMember("habitats") && donnee["habitats"].isArray()) {
//				for (const auto& habitat : donnee["habitats"]) {
//					if (i < habitats.size()) {
//						habitats[i] = stringToHabitat(habitat.asString());
//						i++;
//					}
//					else {
//						throw runtime_error("Trop d'habitats dans 'tuile'.");
//					}
//				}
//			}
//			else {
//				throw runtime_error("Format JSON incorrect : 'habitats' manquant ou non un tableau.");
//			}
//
//			vector<Faune> faunes;
//			if (donnee.isMember("faunes") && donnee["faunes"].isArray()) {
//				for (const auto& faune : donnee["faunes"]) {
//					faunes.push_back(stringToFaune(faune.asString()));
//				}
//			}
//			else {
//				throw runtime_error("Format JSON incorrect : 'faunes' manquant ou non un tableau.");
//			}
//
//			bool donneJetonNature = donnee.get("donneJetonNature", false).asBool();
//
//			// allocation de memoire dynamique
//			if (j >= ensembleTuilesDepart.size()) {
//				ensembleTuilesDepart.resize(j + 1);
//			}
//
//			ensembleTuilesDepart[j].push_back(Tuile(habitats, faunes, donneJetonNature));
//		}
//		j++;
//	}
//}

void GestionTuiles::melangerTuiles(std::vector<Tuile>& tuiles) {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(tuiles.begin(), tuiles.end(), g);
}

///TODO: reflechir à implmenter en stack au lieu de vector
Tuile GestionTuiles::depilerTuile(std::vector<Tuile>& tuiles) {
	if (tuiles.empty()) {
		throw std::out_of_range("Impossible de dépiler : vecteur vide !");
	}

	Tuile tuile = move(tuiles.back());
	tuiles.pop_back();
	return tuile; 
}


void testGestionTuiles() {
	try {
		/*vector<Tuile> ensembleTuiles;
		GestionTuiles::instancierTuiles("tuiles_non_reperes.json", ensembleTuiles);
		GestionTuiles::instancierTuiles("tuiles_reperes.json", ensembleTuiles);*/
		
		//vector<vector<Tuile>> ensembleTuilesDepart;
		//GestionTuiles::instancierTuilesDepart("tuiles_depart.json", ensembleTuilesDepart);

		//for (size_t i = 0; i < ensembleTuilesDepart.size(); ++i) {
		//	cout << "Triplet " << i + 1 << ":\n";
		//	for (const auto& tuile : ensembleTuilesDepart[i]) {
		//		cout << tuile << endl;  // Now this works
		//	}
		//	cout << "----------------------\n";
		//}

		//// Toutes les tuiles (Avant)
		//cout << "Ensemble de Tuiles avant de melanger et depiler:" << endl;
		//for (const auto& tuile : ensembleTuiles) {
		//    cout << tuile << endl;
		//}

		//// Toutes les tuiles melangees (Avant)
		//GestionTuiles::melangerTuiles(ensembleTuiles);
		//cout << "Ensemble de Tuiles apres avoir ete melange sans depiler:" << endl;
		//for (const auto& tuile : ensembleTuiles) {
		//    cout << tuile << endl;
		//}

		////depiler la derniere Tuile
		//Tuile tuileDepilee = GestionTuiles::depilerTuile(ensembleTuiles);
		//cout << "Tuile depilee: " << tuileDepilee << endl;

		//// le reste des tuiles (Apres)
		//cout << "Ensemble de Tuiles apres avoir ete melange et depile:" << endl;
		//for (const auto& tuile : ensembleTuiles) {
		//    cout << tuile << endl;
		//}
	}
	catch (const runtime_error& e) {
		cerr << "Error: " << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Unexpected error: " << e.what() << endl;
	}
}

void testGestionTuiles2() {
	std::vector<Tuile> tuilesNonReperes = GestionTuiles::instancierTuiles("tuiles_non_reperes.json");
	//for (const auto& tuile : tuilesNonReperes) cout << tuile << endl;

	std::vector<Tuile> tuilesReperes = GestionTuiles::instancierTuiles("tuiles_reperes.json");
	//for (const auto& tuile : tuilesReperes) cout << tuile << endl;
	
	///TODO : peut etre qu'il faut fusionner les reperes et nonReperes

	GestionTuiles::melangerTuiles(tuilesNonReperes);
	cout << GestionTuiles::depilerTuile(tuilesNonReperes);

}