
//--------------------------------------------------- Interfaces utilis�es
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
#include "cIndex.h"

//------------------------------------------------------------------ Types 
typedef int tableauHorraire[25];
typedef map <int, int*> mapReferer;
typedef map <int, mapReferer *> mapCible;


// A modifier de place -> sert à sortir les 2 sources avec le plus de Hit
struct sReq
{
    int key;
    int nbHit;

    sReq(int k, int nb) : key(k), nbHit(nb) {}

    bool operator < (const sReq& str) const
    {
		return (nbHit < str.nbHit);
    }
};
typedef vector <sReq> vReqOrdered;

class cJournal
{
public:
	void orderReq ();
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

