#include <iostream>
using namespace std;
#include "cascadia.h"

int main() {
	// cout << "hello world\n" << endl;
	
	//testClassePosition();

	// testClasseTuile();

	//JetonFaune j(Faune::saumon);
	//cout << j;



    GestionInstanciation gestionInstanciation;

    try {
        /*vector<Tuile> ensembleTuiles;
        gestionInstanciation.instancierTuiles("tuiles_non_reperes.json", ensembleTuiles);
        gestionInstanciation.instancierTuiles("tuiles_reperes.json", ensembleTuiles);*/
        vector<vector<Tuile>> ensembleTripletsDepart;
        gestionInstanciation.instancierTripletsDepart("tuiles_depart.json", ensembleTripletsDepart);

        for (size_t i = 0; i < ensembleTripletsDepart.size(); ++i) {
            cout << "Triplet " << i + 1 << ":\n";
            for (const auto& tuile : ensembleTripletsDepart[i]) {
                cout << tuile << endl;  // Now this works
            }
            cout << "----------------------\n";
        }

        //// Toutes les tuiles (Avant)
        //cout << "Ensemble de Tuiles avant de melanger et depiler:" << endl;
        //for (const auto& tuile : ensembleTuiles) {
        //    cout << tuile << endl;
        //}

        //// Toutes les tuiles melangees (Avant)
        //gestionInstanciation.melangerTuiles(ensembleTuiles);
        //cout << "Ensemble de Tuiles apres avoir ete melange sans depiler:" << endl;
        //for (const auto& tuile : ensembleTuiles) {
        //    cout << tuile << endl;
        //}

        ////depiler la derniere Tuile
        //Tuile tuileDepilee = gestionInstanciation.depilerTuile(ensembleTuiles);
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