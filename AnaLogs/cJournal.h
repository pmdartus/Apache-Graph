
//--------------------------------------------------- Interfaces utilis�es
#include <iostream>
#include <map>
using namespace std;
#include "cIndex.h"

//------------------------------------------------------------------ Types 
typedef int tableauHorraire[25];
typedef map <int, int*> mapReferer;
typedef map <int, mapReferer*> mapCible;

class cJournal
{
public:
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

