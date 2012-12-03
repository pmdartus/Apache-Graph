/*************************************************************************
                   cIndex  -  gère les index pour les pages
                             -------------------
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Réalisation de la classe <cIndex> (fichier cIndex.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;

//------------------------------------------------------ Include personnel
#include "cIndex.h"

//------------------------------------------------------------- Constantes


//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques

int cIndex::addUrl (string aUrl)
// Algorithme :
// Cherche l'index que l'on veut ajouter.
// S'il existe, la fonction renvoie son id.
// Sinon elle l'ajout à la map puis renvoi son id.
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
}; //----- Fin de Méthode


string cIndex::findUrl (int aNumIndex)
// Algorithme :
// Parcours toute la map jusqu'à trouver l'id cherché.
// S'il l'a trouve, renvoie l'URL équivalente.
// Sinon renvoie une ERROR+aNumIndex.
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
	cerr<<"Aucune url n'a été trouvé dans pour l'index "<<aNumIndex<<endl;
#endif
		return ("ERROR"+aNumIndex);
	}
}; //----- Fin de Méthode


void cIndex::disp ()
// Algorithme :
// Parcours la map et affiche chaque lien index/URL
{
	for(it = Index.begin(); (it != Index.end()); it++)
	{
		cout << it->first << " -> " << it->second << endl;
	}
}; //----- Fin de Méthode


//-------------------------------------------- Constructeurs - destructeur

cIndex::cIndex ( )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <cIndex>" << endl;
#endif

} //----- Fin de cIndex


cIndex::~cIndex ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <cIndex>" << endl;
#endif
} //----- Fin de ~cIndex


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//------------------------------------------------------- Méthodes privées