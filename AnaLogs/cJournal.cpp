/*************************************************************************
                   cJournal  -  gère les données à importer
                             -------------------
    début                : 12 nov. 2012
    copyright            : (C) 2012 par pmdartus
*************************************************************************/

//---------- Réalisation de la classe <cJournal> (fichier cJournal.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

//------------------------------------------------------ Include personnel
#include "cJournal.h"

//------------------------------------------------------------- Constantes


//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques


int cJournal::dispLogs(int maxHits)
// Algorithme :
//
{
	//Création et initialisation de la nouvelle structure de donnée
	vReqOrdered aReqOrdered = orderLogs();
	vector<sReq>::reverse_iterator it;

	//Affichage des requetes
	it=aReqOrdered.rbegin();
	int i=0;
	while(it!=aReqOrdered.rend()&&(i<maxHits||maxHits==0))
	{
		cout<<Index.findUrl(it->key)<< " ("<<it->nbHit<<" vue(s))"<<endl;
		it++;
		i++;
	}

	return 0;
}; //----- Fin de Méthode


//TODO : Refondre le schmilblik :)
void cJournal::optionNbVisite(int iNbVisite)
// Algorithme :
// 
{
	itCible=mCible.begin();

	while (itCible != mCible.end())
	{
		//Initialisation des variables de parcourt
		int aNbVisite=0;
		itReferer = (*itCible->second).begin();

		//Récupération du nombre de visite
		while (itReferer != (*itCible->second).end() )
		{
			aNbVisite=itReferer->second[24]+aNbVisite;
			++itReferer;
		}

		//Supression de la mémoire allouée dans le cas ou le nombre de visite est inférieur au nombre requis
		if (aNbVisite<iNbVisite)
		{
			itReferer=(*itCible->second).begin();
			while (itReferer != (*itCible->second).end() )
			{
				int* tableau = itReferer->second;
				(*itCible->second).erase(itReferer++);
				delete tableau;
			}

			mCible.erase(itCible++);
		}

		//Sinon passer à la cible suivante
		else
		{
			++itCible;
		}
	}
}; //----- Fin de Méthode


int cJournal::dispIndex()
// Algorithme :
//
{
	Index.disp();

	return 0;
}; //----- Fin de Méthode
	


//-------------------------------------------- Constructeurs - destructeur


cJournal::cJournal ( string cFic, bool html, int heure, string aGraphizFile )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <cChargement>" << endl;
#endif

	bOptionHtml = html;
	iOptionHeure = heure;
	sGraphizFile = aGraphizFile;
	
	fromFile (cFic);
} //----- Fin de cChargement


cJournal::~cJournal ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <cChargement>" << endl;
#endif
} //----- Fin de ~cChargement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


void cJournal::traiterReq(int heure, string referer, string url, string statut)
// Algorithme :
//
{
	//Traitement du referer
	referer.erase(0,1);
	referer.erase(referer.length()-1,1);

	//Suppression de la base pour le referer si l'on vient du site actuel (et pas de l'extérieur)
	size_t found;
	if (referer.find("http://intranet-if.insa-lyon.fr")!=string::npos)
	{
		referer.erase(0,30);
	}
	else if (referer.find("http://if.insa-lyon.fr")!=string::npos)
	{
		referer.erase(0,21);
	}

	// Ajout des Url à l'index
	if (iOptionHeure == -1 || heure==iOptionHeure )
	{
		if (bOptionHtml==true)//Optimisation pour que l'on ne cherche que quand l'option html est active
		{
			// Recherche de l'accès d'un fichier html | prise en compte du fichier racine
			found = url.find(".html");
			if(found!=string::npos || url=="/")
			{
				addReq(url, referer, heure);
			}
		}
		else
		{
			addReq(url, referer, heure);
		}
	}
}; //----- Fin de Méthode


//TODO : traiter le gmt
string cJournal::splitLog(string aLigne, int &aHeure, string &aRequete, string &aReferer, string &aStatut)
// Algorithme :
//
{
	//Récupération des infos bruts depuis la ligne actuelle selon un schéma précis
	istringstream ligneActuelle(aLigne);
	string useless, action;
	
	char date[3];
	ligneActuelle.seekg (aLigne.find_first_of(':')+1, ios_base::beg);
	ligneActuelle>>aHeure;
	ligneActuelle.seekg (15, ios_base::cur);
	ligneActuelle >> action >> aRequete;
	ligneActuelle.seekg (10, ios_base::cur);
	ligneActuelle >> aStatut >> useless >> aReferer;

	if ((aReferer.length()>=3)&&(aStatut=="200")) 
	{
		return action;
	}
	else
	{
#ifdef MAP
cerr << "Statut de la requete non pris en compte : " <<status<< " | "<<action<< endl;
#endif
		return "";
	}
}; //----- Fin de Méthode


//TODO : try catch du père fourra sur la récupération d'une ligne + compteur d'erreur
void cJournal::fromFile (string cFic)
// Algorithme :
//
{
	ifstream fic(cFic, ios::in);  //Ouverture d'un fichier en lecture

	if(fic)
	{
		string ligne; //variable dans laquelle on stock chaque ligne

		while(getline(fic, ligne))  //On lit ligne par ligne
		{

			string sRequete, sReferer, sStatut;
			int iHeure;

			if (splitLog(ligne, iHeure, sRequete, sReferer, sStatut) == "GET")
			{
				//Ajout des données
				traiterReq(iHeure, sReferer, sRequete, sStatut);
			}
			else
			{
#ifdef MAP
	cerr << "Syntaxe de la ligne non valide"<< endl;
#endif
			}
			
		}

#ifdef MAP // Affichage des différentes adresses stockés dans l'index, et la map
	dispLogs(10);
#endif

	cout << "Lecture terminée" <<endl;

	dispLogs(10);

	}
	else
	{
		cerr << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
}; //----- Fin de Méthode

void cJournal::addReq(string sCible, string sReferer, int aHeure)
// Algorithme :
//
{
	//Obtention de l'index pour les Url
	int aCible = Index.addUrl(sCible);
	int aReferer = Index.addUrl(sReferer);

	//Recherche de l'existence de la cible
	itCible=mCible.find(aCible);

	if (itCible!=mCible.end()) //La cible est déjà stockée
	{
		itReferer= (*itCible->second).find(aReferer);

		if (itReferer!=(*itCible->second).end()) //Le Referer est déjà stocké 
		{
			//On incrément la case correspondant à l'heure et au compteur total
			itReferer->second[aHeure]++;
			itReferer->second [24]++;
		}
		
		else //le referer de la cible n'existe pas
		{
			//Création et initialisation du tableau des heures
			int* aTableauHorraire = new (tableauHorraire);
			for( int i=0; i<=24; i++)
			{
				aTableauHorraire[i] =0;
			}
			aTableauHorraire[aHeure]=1;
			aTableauHorraire[24]=1;

			//insertion du tableau dans la map referer associée
			(*itCible->second).insert ( pair<int,int*>(aReferer,aTableauHorraire) );
		}
	}

	else //La cible n'existe pas 
	{
		//Création de la map referer et association avec la cible.
		mapReferer * aMapReferer = new mapReferer;

		int* aTableauHorraire = new (tableauHorraire);
		for( int i=0; i<=24; i++)
		{
			aTableauHorraire [i] =0;
		}
		aTableauHorraire[aHeure]=1;
		aTableauHorraire[24]=1;

		(*aMapReferer).insert ( pair<int,int*>(aReferer,aTableauHorraire) );

		mCible.insert(pair<int,mapReferer*>(aCible,aMapReferer));
	}
}; //----- Fin de Méthode

//TODO : optimiser si que 10 à afficher !!!
vReqOrdered cJournal::orderLogs()
// Algorithme :
//
{
	vReqOrdered aReqOrdered;
	itCible=mCible.begin();

	while (itCible != mCible.end())
	{
		//Initialisation des variables de parcours
		int aNbVisite=0;
		itReferer = (*itCible->second).begin();

		//Récupération du nombre de visite
		while (itReferer != (*itCible->second).end() )
		{
			aNbVisite=itReferer->second[24]+aNbVisite;
			++itReferer;
		}

		//ajout d'une requete dans la structure
		aReqOrdered.push_back(sReq(itCible->first, aNbVisite));

		++itCible;
	}
	
	//tri des requetes
	sort(aReqOrdered.begin(),aReqOrdered.end());

	return aReqOrdered; 
}; //----- Fin de Méthode

//------------------------------------------------------- Méthodes privées
