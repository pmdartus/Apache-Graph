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

//------------------------------------------------------ Include personnel
#include "cJournal.h"
#define MAP2

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


int cJournal::dispIndex()
// Algorithme :
//
{
	Index.disp();

	return 0;
}; //----- Fin de Méthode
	


//-------------------------------------------- Constructeurs - destructeur


cJournal::cJournal ( string cFic, bool html, int heure )
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <cChargement>" << endl;
#endif

	bOptionHtml = html;
	iOptionHeure = heure;
	
	FromFile (cFic)
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
			//Récupération des infos bruts depuis la ligne actuelle selon un schéma précis
			istringstream ligneActuelle(ligne);
			string useless, date, action, url, referer;
			int status;
			ligneActuelle >> useless >> useless >> useless >> date >> useless >> action >> url >> useless >> status >> useless >> referer;

			//Traitement de la requete
			action.erase(0,1);

			if (status == 200 && action=="GET")
			{
				bool bFichierHtml = false;

				//Traitement de la date
				date.erase(0,13);
				date.erase(2);
				int heure = atoi(date.c_str()); //transformation en int
			
				//Traitement du referer
				referer.erase(0,1);
				referer.erase(referer.length()-1,1);

				//Suppression de la basse pour le referer si l'on vient du site actuel (et pas de l'extérieur)
				size_t found;
				found = referer.find("http://intranet-if.insa-lyon.fr/");
				if (found!=string::npos)
				{
					referer.replace(0,31, "");
				}

				// Recherche de l'accès d'un fichier html | prise en compte du fichier racine
				found = url.find(".html");
				if (found!=string::npos || url=="/")
				{
					bFichierHtml=true;
				}

				// Ajout des Url à l'index
				if (heure==iOptionHeure || iOptionHeure==-1 )
				{
					if (bOptionHtml==true)
					{
						if (bFichierHtml==true)
						{
							addReq(url, referer, heure);
						}
					}
					else
					{
						addReq(url, referer, heure);
					}
				}
			}
			else
			{
#ifdef MAP
	cout << "Statut de la requete non pris en compte : " <<status<< " | "<<action<< endl;
#endif
			}
			
		}

#ifdef MAP // Affichage des différentes adresses stockés dans l'index, et la map
	int i=2;
	//Journal.OptionNbVisite(i);
	//Journal.dispLogs();
	Journal.dispIndex();
#endif

	}
	else
	{
#ifdef MAP
	cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
#endif
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

//------------------------------------------------------- Méthodes privées
