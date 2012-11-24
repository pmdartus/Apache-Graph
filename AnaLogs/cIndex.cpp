#include "cIndex.h"

using namespace std;


//Recherche d'une Url à partir de son index
string cIndex::findUrl (int aNumIndex)
{
	it=Index.begin();

	// Boucle sur la Map jusqu'a obtenir la bonne occurence
	for(it = Index.begin(); (it != Index.end()) && (it->second!= aNumIndex); it++)
	{
	}

	// Retour de l'Url 
	if (it->second==aNumIndex)
	{
		return it->first;
	}
	else
	{
	#ifdef MAP
			cout<<"L'url recherche n'a pas était trouvé dans l'index"<<aNumIndex<<endl;
	#endif
	}
		
}


// Ajout d'un Url à la liste -> retourne le numero de l'index
int cIndex::addUrl (string aUrl)
{
	it = Index.find(aUrl);

	// Si trouvé renvoi le numero de l'index
	if (it!=Index.end()) 
	{
		#ifdef MAP
		cout<<"L'url"<<aUrl<<"existe déjà avec l'index"<<it->second<<endl;
		#endif
		return it->second;
	}
	// Sinon revoi l'index de l'Url inséré
	else
	{
		int iIndexAjout = Index.size()+1;
		Index.insert ( pair<string,int>(aUrl,iIndexAjout) );

		#ifdef MAP
		cout<<"Ajout de l'url"<<aUrl<<"dans l'index"<<iIndexAjout<<endl;
		#endif

		return iIndexAjout;
	}
}

//Affichage à l'écran des différentes valeurs stockées dans l'index
void cIndex::disp ()
{
	for(it = Index.begin(); (it != Index.end()); it++)
	{
		cout << it->first << " -> " << it->second << endl;
	}
}

cIndex::cIndex(void)
{
}

// Destruction des occurences
cIndex::~cIndex(void)
{
	Index.clear();
}
