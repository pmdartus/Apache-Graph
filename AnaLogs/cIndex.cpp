#include <iostream>
#include <map>
#include "cIndex.h"

using namespace std;


//Recherche d'une Url � partir de son index
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
			cout<<"L'url recherche n'a pas �tait trouv� dans l'index"<<aNumIndex<<endl;
	#endif
	}
		
}


// Ajout d'un Url � la liste -> retourne le numero de l'index
int cIndex::addUrl (string aUrl)
{
	it = Index.find(aUrl);

	// Si trouv� renvoi le numero de l'index
	if (it!=Index.end()) 
	{
		#ifdef MAP
		cout<<"L'url"<<aUrl<<"existe d�j� avec l'index"<<it->second<<endl;
		#endif
		return it->second;
	}
	// Sinon revoi l'index de l'Url ins�r�
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


cIndex::~cIndex(void)
{
	// Destruction des occurences
	Index.clear();
}
