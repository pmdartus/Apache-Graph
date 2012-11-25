
//--------------------------------------------------- Interfaces utilis�es
#include <iostream>
#include <map>
using namespace std;
#include "cIndex.h"

//------------------------------------------------------------------ Types 
typedef int tableauHorraire[25];
typedef map <int, int*> mapReferer;
typedef map <int, mapReferer *> mapCible;

// A modifier de place -> sert à sortir les 2 sources avec le plus de Hit
struct RequetePlusVues
{
    int key;
    int nbHit;

    RequetePlusVues(int k, int nb) : key(k), nbHit(nb) {}

    bool operator < (const RequetePlusVues& str) const
    {
		return (nbHit < str.nbHit);
    }
};

class cJournal
{
public:
	void OptionNbVisite(int iNbVisite);
	void addReq(string sCible, string sReferer, int aHeure);
	int dispLogs();
	int dispIndex();
	cJournal(void);
	~cJournal(void);

private:
	mapCible mCible;
	cIndex Index;
	mapReferer::iterator itReferer;
	mapCible::iterator itCible;

};

