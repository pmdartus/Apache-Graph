#include <iostream>
#include <map>
#include "cIndex.h"

using namespace std;


//Recherche d'une Url � partir de son index
string cIndex::findUrl (int aNumIndex)
{
	it=Index.begin();

	// Boucle sur la Map jusqu'a obtenir la bonne occurence
	while (it->second=!aNumIndex && it=!Index.end)
	{
	}

	// Retour de l'Url 
	if (it->second==aNumIndex)
	{
		return it->first
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
	if (it->first==aUrl) 
	{
		return it->second;
	}
	// Sinon revoi l'index de l'Url ins�r�
	else
	{
		Index.insert ( pair<string,int>(aUrl,Index.size+1) );
		return Index.size;
	}
}

cIndex::cIndex(void)
{
}


cIndex::~cIndex(void)
{
	// Destruction des occurences
	Index.clear;
}
