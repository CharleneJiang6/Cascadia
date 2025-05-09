#include <iostream>
using namespace std;
#include "cascadia.h"

int main() {
	// cout << "hello world\n" << endl;
	
	//testClassePosition();

	// testClasseTuile();

	//JetonFaune j(Faune::saumon);
	//cout << j;



    GestionInstanciation gestion;

    try {
        vector<Tuile> tuiles;
        gestion.instancierTuiles("tuiles_non_reperes.json", tuiles);
        gestion.instancierTuiles("tuiles_reperes.json", tuiles);

        // Toutes les tuiles (Avant)
        cout << "Ensemble de Tuiles avant de melanger et depiler:" << std::endl;
        for (const auto& tuile : tuiles) {
            cout << tuile << std::endl;
        }

        // Toutes les tuiles melangees (Avant)
        gestion.melangerTuiles(tuiles);
        cout << "Ensemble de Tuiles apres avoir ete melange sans depiler:" << std::endl;
        for (const auto& tuile : tuiles) {
            cout << tuile << std::endl;
        }

        //depiler la derniere Tuile
        Tuile tuileDepilee = gestion.depilerTuile(tuiles);
        cout << "Tuile depilee: " << tuileDepilee << std::endl;

        // le reste des tuiles (Apres)
        cout << "Ensemble de Tuiles apres avoir ete melange et depile:" << std::endl;
        for (const auto& tuile : tuiles) {
            cout << tuile << std::endl;
        }
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }
}