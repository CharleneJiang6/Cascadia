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
        vector<Tuile> tuiles = gestion.instancierTuiles("tuiles_non_reperes.json");
        //vector<Tuile> tuiles = gestion.instancierTuiles("tuiles_reperes.json");
        
        for (const auto& tuile : tuiles) {
            cout << tuile << endl;
        }
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }
}