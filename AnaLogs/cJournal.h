
//--------------------------------------------------- Interfaces utilis�es
#include <iostream>
#include <map>
using namespace std;

//------------------------------------------------------------------ Types 
typedef int tableauHorraire[25];
typedef map <int, int*> mapReferer;
typedef map <int, mapReferer> mapCible;

class cJournal
{
public:
	void addReq(int aCible, int aReferer, int aHeure);
	cJournal(void);
	~cJournal(void);
private:

	mapCible mCible;
	mapReferer::iterator itReferer;
	mapCible::iterator itCible;

};

