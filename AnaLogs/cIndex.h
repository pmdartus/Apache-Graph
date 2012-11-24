
//--------------------------------------------------- Interfaces utilis�es
#include <string>
#include <iostream>
#include <map>
using namespace std;

//------------------------------------------------------------------ Types 
typedef map <string, int> mIndex; // Établis un lien d’id entre une adresse et un numero

class cIndex
{
private:
	mIndex Index;
	mIndex::iterator it;
public:
	int addUrl (string aUrl);
	string findUrl (int aNumIndex);
	void disp ();

	cIndex(void);
	~cIndex(void);
};
