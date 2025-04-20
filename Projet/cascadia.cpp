#include <iostream>
#include "cascadia.h"
using namespace std;

ostream& operator<<(ostream& flux, const Position& p)
{
	flux << "(" << p.getQ() << "," << p.getR() << "," << p.getS() << ")";
	return flux;
}
