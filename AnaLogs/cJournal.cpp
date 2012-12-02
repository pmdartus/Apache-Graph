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


//TODO : traiter le gmt
void cJournal::traiterReq(string date, string referer, string url)
// Algorithme :
//
{
	if (url.length()>1) //Pour être sur que l'on ne supprime pas une chaine vide.
	{
		string statut = url;
		statut.erase(0, statut.length()-3); //récupération du statut
		url.erase(url.length()-14, 14); //puis suppression dans la requete suppression du statut
		url.erase(0, 5); //et de l'action

		if (statut == "200")
		{
			bool bFichierHtml = false;

			date.erase(0,13);
			date.erase(2);
			int heure = atoi(date.c_str()); //transformation en int
			
			//Traitement du referer
			referer.erase(0,1);
			referer.erase(referer.length()-3,3);

			//Suppression de la base pour le referer si l'on vient du site actuel (et pas de l'extérieur)
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
cerr << "Statut de la requete non pris en compte : " <<status<< " | "<<action<< endl;
#endif
		}
	}
}; //----- Fin de Méthode


bool cJournal::splitLog(string aLigne, string &aDate, string &aRequete, string &aReferer)
// Algorithme :
//
{
	bool regexOk = false;

	regex_constants::match_flag_type fl = regex_constants::match_default;//flag : option de la regex
			
	//----------------------------- Récupération de la date ------------------------------------------------------
	cmatch date;
	regex dateRx("([0-9]){2}/([a-zA-z]{3})/([0-9]){4}:([0-9]){2}:([0-9]){2}:([0-9]){2}(.){2}([0-9]){4}");
	regexOk = regex_search(aLigne.c_str(),date, dateRx, fl);
	aDate = date[0];
#if MAP
	cout << sDate << endl;
#endif
			
	//----------------------- Récupération de l'url et du statut --------------------------------------------------
	cmatch requete;
	regex requeteRx("\"GET(.)(.){1,}(HTTP\/1\.1)\" [0-9]{3}"); // sélection du GET et non post interne à la recherche (remplace [a-zA-Z]{3,5} ) qui serait plus générique.
	regexOk = regex_search(aLigne.c_str(),requete, requeteRx, fl);
	aRequete = requete[0];
#if MAP
	cout << sRequete << endl;
#endif
			
	//----------------------------- Récupération du referer ------------------------------------------------------
	cmatch referer;
	regex refererRx("\"(http://(.){1,}|-)\".\"");
	regexOk = regex_search(aLigne.c_str(), referer, refererRx, fl);
	aReferer = referer[0];
#if MAP
	cout << sReferer << endl;
#endif

	return regexOk;
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

		//int i = 0;
		while(getline(fic, ligne))  //On lit ligne par ligne
		{
			//cout << i++ << endl;

			string sDate, sRequete, sReferer;

			if (splitLog(ligne, sDate, sRequete, sReferer))
			{
				//Ajout des données
				traiterReq(sDate, sReferer, sRequete);
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
